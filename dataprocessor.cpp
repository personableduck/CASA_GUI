#include <iostream>
#include <fstream>

#include "dataprocessor.h"
#include <cmath>
#include <algorithm>

#include "globals.h"

using namespace std;

DataProcessor::DataProcessor() :
    fps(5.0)
{}

DataProcessor::~DataProcessor()
{}

int DataProcessor::addTrack(string coordsFilename, string timeFilename, bool performCalcs)
{
    // Set default track values
    track currTrack;
    currTrack.numFrames = 0;
    currTrack.curvilinearVel = numeric_limits<double>::quiet_NaN();
    currTrack.straightLineVel = numeric_limits<double>::quiet_NaN();
    currTrack.avgPathVel = numeric_limits<double>::quiet_NaN();
    currTrack.linearity = numeric_limits<double>::quiet_NaN();
    currTrack.straightness = numeric_limits<double>::quiet_NaN();
    currTrack.wobble = numeric_limits<double>::quiet_NaN();
    currTrack.beatCrossFrequency = numeric_limits<double>::quiet_NaN();
    currTrack.amplitudeLateralHeadDisplacement = numeric_limits<double>::quiet_NaN();
    currTrack.meanAngularDisplacement = numeric_limits<double>::quiet_NaN();

    // Parse file containing coordinates
    ifstream infile;
    infile.open(coordsFilename);

    if (!infile.is_open())
        return CANNOT_OPEN_FILE;

    string line;
    while (getline(infile, line))
    {
        coord currCoord;

        size_t commaPos1 = line.find(',', 0);
        size_t commaPos2 = line.find(',', commaPos1 + 1);

        string xCoord = line.substr(0, commaPos1);
        string yCoord = line.substr(commaPos1 + 1, commaPos2);
        string zCoord = line.substr(commaPos2 + 1, line.size());

        if (xCoord == "NaN" || yCoord == "NaN" || zCoord == "NaN")
            continue;

        // Get the x, y, and z values of the current coordinate being parsed
        currCoord.x = stod(xCoord);
        currCoord.y = stod(yCoord);
        currCoord.z = stod(zCoord);
        currTrack.coords.push_back(currCoord);
    }

    infile.close();

    // Parse file containing starting and ending frames
    infile.open(timeFilename);

    if (!infile.is_open())
        return CANNOT_OPEN_FILE;

    getline(infile, line);
    size_t commaPos = line.find(',', 0);
    string startFrame = line.substr(0, commaPos);
    string endFrame = line.substr(commaPos + 1, line.size());

    if (startFrame == "NaN" || endFrame == "NaN")
        return NOT_A_NUMBER;

    // Get the number of frames corresponding to the track being added
    currTrack.numFrames = stoi(endFrame) - stoi(startFrame) + 1;

    if (performCalcs)
    {
        int retval;
        if ((retval = calcAllTrackParameters(&currTrack)) < 0)
            return retval;
    }

    tracks.push_back(currTrack);

    return 0;
}

void DataProcessor::clearTracks()
{
    size_t numTracks = tracks.size();
    for (size_t i = 0; i < numTracks; i++)
    {
        tracks[i].coords.clear();
    }
    tracks.clear();
}

// Performs calculations of all parameters of a given track
int DataProcessor::calcAllTrackParameters(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    int retval;

    if ((retval = calcCurvilinearVel(t)) < 0                    ||
        (retval = calcStraightLineVel(t)) < 0                   ||
        (retval = calcAvgPathVel(t)) < 0                        ||
        (retval = calcLinearity(t)) < 0                         ||
        (retval = calcStraightness(t)) < 0                      ||
        (retval = calcWobble(t)) < 0                            ||
        (retval = calcBeatCrossFrequency(t)) < 0                ||
        (retval = calcAmplitudeLateralHeadDisplacement(t)) < 0  ||
        (retval = calcMeanAngularDisplacement(t)) < 0           )
        return retval;

    return 0;
}

int DataProcessor::calcCurvilinearVel(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    // Calculate the sum of the distances between all pairs of consecitive coordinates
    double totalDistance = 0;
    for (unsigned int i = 1; i < t->coords.size(); i++)
    {
        totalDistance += sqrt(pow(t->coords[i].x - t->coords[i - 1].x, 2)
                            + pow(t->coords[i].y - t->coords[i - 1].y, 2)
                            + pow(t->coords[i].z - t->coords[i - 1].z, 2));
    }

    t->curvilinearVel = totalDistance / (t->numFrames * (1 / fps));

    return 0;
}

int DataProcessor::calcStraightLineVel(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    // Calculate the distance between the first and last coordinate and divide by time
    t->straightLineVel = sqrt(pow(t->coords[t->coords.size() - 1].x - t->coords[0].x, 2)
                            + pow(t->coords[t->coords.size() - 1].y - t->coords[0].y, 2)
                            + pow(t->coords[t->coords.size() - 1].z - t->coords[0].z, 2))
                            / (t->numFrames * (1 / fps));

    return 0;
}

// y(i) = (1/2N+1)[y(i+N)+y(i+N-1)+...+y(i-N)]
int DataProcessor::calcAvgPathVel(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    const int MAX_N = 2;
    int N = 0;
    unsigned int numCoords = (unsigned int)t->coords.size();
    for (unsigned int i = 0; i < numCoords; i++)
    {
        unsigned int upperBound = numCoords - MAX_N;
        if (i < MAX_N && i >= upperBound)
        {
            unsigned int j = numCoords - i - 1;
            N = (i < j) ? i : j;
        }
        else if (i < MAX_N)
            N = i;
        else if (i >= upperBound)
            N = numCoords - i - 1;
        else
            N = MAX_N;

        coord c;
        c.x = 0;
        c.y = 0;
        c.z = 0;

        for (int j = -N; j <= N; j++)
        {
            c.x += t->coords[i + j].x;
            c.y += t->coords[i + j].y;
            c.z += t->coords[i + j].z;
        }

        c.x /= (2*N + 1);
        c.y /= (2*N + 1);
        c.z /= (2*N + 1);

        t->avgPathCoords.push_back(c);
    }

    double totalDistance = 0;

    for (unsigned int i = 1; i < t->avgPathCoords.size(); i++)
    {
        totalDistance += sqrt(pow(t->avgPathCoords[i].x - t->avgPathCoords[i - 1].x, 2)
                            + pow(t->avgPathCoords[i].y - t->avgPathCoords[i - 1].y, 2)
                            + pow(t->avgPathCoords[i].z - t->avgPathCoords[i - 1].z, 2));
    }

    t->avgPathVel = totalDistance / (t->numFrames * (1 / fps));

    return 0;
}

// LIN = VSL/VCL
int DataProcessor::calcLinearity(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    if (_isnan(t->straightLineVel) || _isnan(t->curvilinearVel) || t->curvilinearVel == 0)
    {
        t->linearity = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    t->linearity = (t->straightLineVel / t->curvilinearVel) * 100;

    return 0;
}

// LIN = VSL/VAP
int DataProcessor::calcStraightness(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    if (_isnan(t->straightLineVel) || _isnan(t->avgPathVel) || t->avgPathVel == 0)
    {
        t->straightness = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    t->straightness = (t->straightLineVel / t->avgPathVel) * 100;

    return 0;
}

// LIN = VAP/VCL
int DataProcessor::calcWobble(track* t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    if (_isnan(t->avgPathVel) || _isnan(t->curvilinearVel) || t->curvilinearVel == 0)
    {
        t->wobble = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    t->wobble = (t->avgPathVel / t->curvilinearVel) * 100;

    return 0;
}

// Functions to calculate beat cross frequency
DataProcessor::Orientation DataProcessor::getOrientation(Point p, Point q, Point r) const
{
    double determinant = (q.x - p.x)*(r.y - p.y) - (r.x - p.x)*(q.y - p.y);
    if (determinant == 0) return COLLINEAR;
    return (determinant < 0) ? CLOCKWISE : COUNTERCLOCKWISE;
}

bool DataProcessor::doIntersect(Point p1, Point q1, Point p2, Point q2) const
{
    Orientation o1 = getOrientation(p1, q1, p2);
    Orientation o2 = getOrientation(p1, q1, q2);
    Orientation o3 = getOrientation(p2, q2, p1);
    Orientation o4 = getOrientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == COLLINEAR && o2 == COLLINEAR && o3 == COLLINEAR && o4 == COLLINEAR)
    {
        if ((p2.x > min(p1.x, q1.x) && p2.x < max(p1.x, q1.x)) || (q2.x > min(p1.x, q1.x) && q2.x < max(p1.x, q1.x)))
            return true;
    }

    return false;
}

int DataProcessor::calcBeatCrossFrequency(track *t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    const int MAX_N = 2;
    int N = 0;
    unsigned int numCoords = (unsigned int)t->coords.size();
    int numCrosses = 0;
    for (unsigned int i = 0; i < numCoords - 1; i++)
    {
        unsigned int upperBound = numCoords - 1 - MAX_N;
        if (i < MAX_N && i >= upperBound)
        {
            unsigned int j = numCoords - 1 - i - 1;
            N = (i < j) ? i : j;
        }
        else if (i < MAX_N)
            N = i;
        else if (i >= upperBound)
            N = numCoords - 1 - i - 1;
        else
            N = MAX_N;

        Point CLPathPointP(t->coords[i].x, t->coords[i].y);
        Point CLPathPointQ(t->coords[i + 1].x, t->coords[i + 1].y);
        for (int j = -N; j <= N; j++)
        {
            Point AvgPathP(t->avgPathCoords[i + j].x, t->avgPathCoords[i + j].y);
            Point AvgPathQ(t->avgPathCoords[i + j + 1].x, t->avgPathCoords[i + j + 1].y);

            if (doIntersect(CLPathPointP, CLPathPointQ, AvgPathP, AvgPathQ))
            {
                numCrosses++;
                break;
            }
        }
    }

    t->beatCrossFrequency = (double)numCrosses / (t->numFrames * (1 / fps));

    return 0;
}

int DataProcessor::calcAmplitudeLateralHeadDisplacement(track *t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    // Calculate the maximum distance between a coordinate and its corresponding
    // smoothed coordinate for the given track
    unsigned int numCoords = (unsigned int)t->coords.size();
    double ALHmax = 0;
    for (unsigned int i = 0; i < numCoords; i++)
    {
        double riser = 2 * sqrt(pow(t->coords[i].x - t->avgPathCoords[i].x, 2)
                          + pow(t->coords[i].y - t->avgPathCoords[i].y, 2));
        if (riser > ALHmax)
            ALHmax = riser;
    }

    t->amplitudeLateralHeadDisplacement = ALHmax;

    return 0;
}

// Functions to calculate mean angular displacement
long double DataProcessor::dot(coord pCommon, coord p1, coord p2) const
{
    return (p1.x - pCommon.x) * (p2.x - pCommon.x) + (p1.y - pCommon.y) * (p2.y - pCommon.y);
}

long double DataProcessor::productOfVectorLengths(coord pCommon, coord p1, coord p2) const
{
    return sqrt(pow(p1.x - pCommon.x, 2) + pow(p1.y - pCommon.y, 2)) * sqrt(pow(p2.x - pCommon.x, 2) + pow(p2.y - pCommon.y, 2));
}

int DataProcessor::calcMeanAngularDisplacement(track *t)
{
    if (!t)
        return ILLEGAL_ARGUMENT;

    long double totAngDisp = 0;
    unsigned int numCoords = (unsigned int)t->coords.size();
    for (unsigned int i = 1; i < numCoords - 1; i++)
    {
        // Determine the angular displacement between the line segment connecting
        // the current coordinate to the previous coordinate and the line segment
        // connecting the current coordinate to the next coordinate
        coord pCommon = t->coords[i];
        coord p1 = t->coords[i - 1];
        coord p2 = t->coords[i + 1];
        totAngDisp += 180 - (acos(dot(pCommon, p1, p2) / productOfVectorLengths(pCommon, p1, p2)) * 180.0 / PI);
    }

    t->meanAngularDisplacement = totAngDisp / (t->numFrames * (1 / fps));

    return 0;
}

int DataProcessor::calcAllSampleMotilityValues()
{
    int retval;

    if ((retval = calcPercentMotile()) < 0          ||
        (retval = calcPercentImmotile()) < 0        ||
        (retval = calcPercentHyperactivated()) < 0  ||
        (retval = calcPercentRapidAndLinear()) < 0  ||
        (retval = calcPercentProgMotile()) < 0      ||
        (retval = calcPercentNonProgMotile()) < 0   )
        return retval;

    return 0;
}
int DataProcessor::calcPercentMotile()
{
    int numMotile = 0;

    unsigned int numTracks = (unsigned int)tracks.size();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        if (tracks[i].avgPathVel > 5.0)
            numMotile++;
    }

    sampleMotilityValues.percentMotile = ((double)numMotile / numTracks) * 100;

    return 0;
}
int DataProcessor::calcPercentImmotile()
{
    int numImmotile = 0;

    unsigned int numTracks = (unsigned int)tracks.size();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        if (tracks[i].avgPathVel <= 5.0)
            numImmotile++;
    }

    sampleMotilityValues.percentImmotile = ((double)numImmotile / numTracks) * 100;

    return 0;
}
int DataProcessor::calcPercentHyperactivated()
{
    int numHyperactivated = 0;

    unsigned int numTracks = (unsigned int)tracks.size();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        if (tracks[i].curvilinearVel > 150 && tracks[i].linearity <= 50 && tracks[i].amplitudeLateralHeadDisplacement > 7.0)
            numHyperactivated++;
    }

    sampleMotilityValues.percentHyperactivated = ((double)numHyperactivated / numTracks) * 100;

    return 0;
}
int DataProcessor::calcPercentRapidAndLinear()
{
    int numRapidAndLinear = 0;

    unsigned int numTracks = (unsigned int)tracks.size();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        if (tracks[i].avgPathVel > 25.0 && tracks[i].straightness > 75.0 && tracks[i].amplitudeLateralHeadDisplacement > 4.5)
            numRapidAndLinear++;
    }

    sampleMotilityValues.percentRapidAndLinear = ((double)numRapidAndLinear / numTracks) * 100;

    return 0;
}
int DataProcessor::calcPercentProgMotile()
{
    int numProgMotile = 0;

    unsigned int numTracks = (unsigned int)tracks.size();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        if (tracks[i].avgPathVel > 25.0 && tracks[i].straightness > 75.0)
            numProgMotile++;
    }

    sampleMotilityValues.percentProgMotile = ((double)numProgMotile / numTracks) * 100;

    return 0;
}
int DataProcessor::calcPercentNonProgMotile()
{
    int numNonProgMotile = 0;

    unsigned int numTracks = (unsigned int)tracks.size();
    for (unsigned int i = 0; i < numTracks; i++)
    {
        if (tracks[i].avgPathVel > 5.0 && (tracks[i].avgPathVel <= 25.0 || tracks[i].straightness <= 75.0))
            numNonProgMotile++;
    }

    sampleMotilityValues.percentNonProgMotile = ((double)numNonProgMotile / numTracks) * 100;

    return 0;
}

/* Getters Implementation Begin */

int DataProcessor::getXCoord(unsigned int trackIndex, unsigned int coordIndex, double& x) const
{
    if (trackIndexIsOutOfBounds(trackIndex) || coordIndexIsOutOfBounds(trackIndex, coordIndex))
        return INDEX_OUT_OF_BOUNDS;

    x = tracks[trackIndex].coords[coordIndex].x;
    return 0;
}
int DataProcessor::getYCoord(unsigned int trackIndex, unsigned int coordIndex, double& y) const
{
    if (trackIndexIsOutOfBounds(trackIndex) || coordIndexIsOutOfBounds(trackIndex, coordIndex))
        return INDEX_OUT_OF_BOUNDS;

    y = tracks[trackIndex].coords[coordIndex].y;
    return 0;
}
int DataProcessor::getZCoord(unsigned int trackIndex, unsigned int coordIndex, double& z) const
{
    if (trackIndexIsOutOfBounds(trackIndex) || coordIndexIsOutOfBounds(trackIndex, coordIndex))
        return INDEX_OUT_OF_BOUNDS;

    z = tracks[trackIndex].coords[coordIndex].z;
    return 0;
}

int DataProcessor::getXAvgPathCoord(unsigned int trackIndex, unsigned int coordIndex, double& x) const
{
    if (trackIndexIsOutOfBounds(trackIndex) || avgPathCoordIndexIsOutOfBounds(trackIndex, coordIndex))
        return INDEX_OUT_OF_BOUNDS;

    x = tracks[trackIndex].avgPathCoords[coordIndex].x;
    return 0;
}
int DataProcessor::getYAvgPathCoord(unsigned int trackIndex, unsigned int coordIndex, double& y) const
{
    if (trackIndexIsOutOfBounds(trackIndex) || avgPathCoordIndexIsOutOfBounds(trackIndex, coordIndex))
        return INDEX_OUT_OF_BOUNDS;

    y = tracks[trackIndex].avgPathCoords[coordIndex].y;
    return 0;
}
int DataProcessor::getZAvgPathCoord(unsigned int trackIndex, unsigned int coordIndex, double& z) const
{
    if (trackIndexIsOutOfBounds(trackIndex) || avgPathCoordIndexIsOutOfBounds(trackIndex, coordIndex))
        return INDEX_OUT_OF_BOUNDS;

    z = tracks[trackIndex].avgPathCoords[coordIndex].z;
    return 0;
}

int DataProcessor::getCurvilinearVel(unsigned int trackIndex, double& vcl) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    vcl = tracks[trackIndex].curvilinearVel;
    return 0;
}
int DataProcessor::getStraightLineVel(unsigned int trackIndex, double& vsl) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    vsl = tracks[trackIndex].straightLineVel;
    return 0;
}
int DataProcessor::getAvgPathVel(unsigned int trackIndex, double& vap) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    vap = tracks[trackIndex].avgPathVel;
    return 0;
}
int DataProcessor::getLinearity(unsigned int trackIndex, double& linearity) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    linearity = tracks[trackIndex].linearity;
    return 0;
}
int DataProcessor::getStraightness(unsigned int trackIndex, double& straightness) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    straightness = tracks[trackIndex].straightness;
    return 0;
}
int DataProcessor::getWobble(unsigned int trackIndex, double& wobble) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    wobble = tracks[trackIndex].wobble;
    return 0;
}
int DataProcessor::getBeatCrossFrequency(unsigned int trackIndex, double& bcf) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    bcf = tracks[trackIndex].beatCrossFrequency;
    return 0;
}
int DataProcessor::getAmplitudeLateralHeadDisplacement(unsigned int trackIndex, double& alh) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    alh = tracks[trackIndex].amplitudeLateralHeadDisplacement;
    return 0;
}
int DataProcessor::getMeanAngularDisplacement(unsigned int trackIndex, double &mad) const
{
    if (trackIndexIsOutOfBounds(trackIndex))
        return INDEX_OUT_OF_BOUNDS;

    mad = tracks[trackIndex].meanAngularDisplacement;
    return 0;
}
int DataProcessor::getPercentHyperactivated(double &percent) const
{
    if (_isnan(sampleMotilityValues.percentHyperactivated))
    {
        percent = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    percent = sampleMotilityValues.percentHyperactivated;
    return 0;
}
int DataProcessor::getPercentRapidAndLinear(double &percent) const
{
    if (_isnan(sampleMotilityValues.percentRapidAndLinear))
    {
        percent = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    percent = sampleMotilityValues.percentRapidAndLinear;
    return 0;
}
int DataProcessor::getPercentProgMotile(double &percent) const
{
    if (_isnan(sampleMotilityValues.percentProgMotile))
    {
        percent = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    percent = sampleMotilityValues.percentProgMotile;
    return 0;
}
int DataProcessor::getPercentNonProgMotile(double &percent) const
{
    if (_isnan(sampleMotilityValues.percentNonProgMotile))
    {
        percent = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    percent = sampleMotilityValues.percentNonProgMotile;
    return 0;
}
int DataProcessor::getPercentMotile(double &percent) const
{
    if (_isnan(sampleMotilityValues.percentMotile))
    {
        percent = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    percent = sampleMotilityValues.percentMotile;
    return 0;
}
int DataProcessor::getPercentImmotile(double &percent) const
{
    if (_isnan(sampleMotilityValues.percentImmotile))
    {
        percent = numeric_limits<double>::quiet_NaN();
        return NOT_A_NUMBER;
    }

    percent = sampleMotilityValues.percentImmotile;
    return 0;
}

/* Getters Implementation End */

// Private member functions
bool DataProcessor::trackIndexIsOutOfBounds(unsigned int trackIndex) const
{
    return (trackIndex > tracks.size() - 1);
}

bool DataProcessor::coordIndexIsOutOfBounds(unsigned int trackIndex, unsigned int coordIndex) const
{
    return (coordIndex > tracks[trackIndex].coords.size() - 1);
}

bool DataProcessor::avgPathCoordIndexIsOutOfBounds(unsigned int trackIndex, unsigned int coordIndex) const
{
    return (coordIndex > tracks[trackIndex].avgPathCoords.size() - 1);
}

// Function for debugging
void DataProcessor::printTracks()
{
    unsigned int totNumTracks = (unsigned int)tracks.size();
    cout << "TOTAL NUMBER OF TRACKS: " << totNumTracks << endl;
    for (unsigned int i = 0; i < totNumTracks; i++)
    {
        cout << "TRACK #" << i + 1 << ":" << endl;
        cout << "Total number of frames: " << tracks[i].numFrames << endl;
        cout << "Curvilinear velocity: " << tracks[i].curvilinearVel << endl;
        cout << "Straight-line velocity: " << tracks[i].straightLineVel << endl;
        cout << "Average-path velocity: " << tracks[i].avgPathVel << endl;
        cout << "Linearity: " << tracks[i].linearity << endl;
        cout << "Straightness: " << tracks[i].straightness << endl;
        cout << "Wobble: " << tracks[i].wobble << endl;
        cout << "Beat Cross Frequency: " << tracks[i].beatCrossFrequency << endl;
        cout << "Amplitude of Lateral Head Displacement: " << tracks[i].amplitudeLateralHeadDisplacement << endl;
        cout << "Mean Angular Displacement: " << tracks[i].meanAngularDisplacement << endl;
        cout << "Number of Coords: " << tracks[i].coords.size() << endl;
        cout << "Number of AvgPathCoords: " << tracks[i].avgPathCoords.size() << endl;

//        for (unsigned int j = 0; j < tracks[i].coords.size(); j++)
//        {
//            cout << j << "," << tracks[i].coords[j].x << "," << tracks[i].coords[j].y << "," << tracks[i].coords[j].z << endl;
//        }
//        for (unsigned int j = 0; j < tracks[i].avgPathCoords.size(); j++)
//        {
//            cout << j << "," << tracks[i].avgPathCoords[j].x << "," << tracks[i].avgPathCoords[j].y << "," << tracks[i].avgPathCoords[j].z << endl;
//        }
    }
}
