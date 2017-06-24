#ifndef DATAPROCESSOR
#define DATAPROCESSOR

#include <vector>
#include <string>
#include <limits>

class DataProcessor
{
private:
    struct coord
    {
        double x, y, z;
    };

    struct track
    {
        std::vector<coord> coords;
        int numFrames;

        std::vector<coord> avgPathCoords;
        double curvilinearVel;
        double straightLineVel;
        double avgPathVel;
        double linearity;
        double straightness;
        double wobble;
        double beatCrossFrequency;
        double amplitudeLateralHeadDisplacement;
        double meanAngularDisplacement;
    };

    // Member variables
    std::vector<track> tracks;

    struct sample_motility_values
    {
        sample_motility_values() :
            percentMotile(std::numeric_limits<double>::quiet_NaN()),
            percentImmotile(std::numeric_limits<double>::quiet_NaN()),
            percentHyperactivated(std::numeric_limits<double>::quiet_NaN()),
            percentRapidAndLinear(std::numeric_limits<double>::quiet_NaN()),
            percentProgMotile(std::numeric_limits<double>::quiet_NaN()),
            percentNonProgMotile(std::numeric_limits<double>::quiet_NaN())
        {}

        double percentMotile;
        double percentImmotile;
        double percentHyperactivated;
        double percentRapidAndLinear;
        double percentProgMotile;
        double percentNonProgMotile;
    } sampleMotilityValues;

    double fps;

    // Private member functions
    bool trackIndexIsOutOfBounds(unsigned int trackIndex) const;
    bool coordIndexIsOutOfBounds(unsigned int trackIndex, unsigned int coordIndex) const;
    bool avgPathCoordIndexIsOutOfBounds(unsigned int trackIndex, unsigned int coordIndex) const;

    // Helper data structures and fuctions for calcBeatCrossFrequency
    struct Point
    {
        Point(double x, double y) { this->x = x; this->y = y; }
        double x, y;
    };
    enum Orientation { COLLINEAR, CLOCKWISE, COUNTERCLOCKWISE };
    Orientation getOrientation(Point p, Point q, Point r) const;
    bool doIntersect(Point p1, Point q1, Point p2, Point q2) const;

    // Helper functions for calcMeanAngularDisplacement
    long double dot(coord pCommon, coord p1, coord p2) const;
    long double productOfVectorLengths(coord pCommon, coord p1, coord p2) const;

public:
    DataProcessor();
    ~DataProcessor();

    int addTrack(std::string coordsFilename, std::string timeFilename, bool performCalcs);
    void clearTracks();

    // Motility parameter calculation functions
    int calcAllTrackParameters(track* t);
    int calcCurvilinearVel(track* t);
    int calcStraightLineVel(track* t);
    int calcAvgPathVel(track* t);
    int calcLinearity(track* t);
    int calcStraightness(track* t);
    int calcWobble(track* t);
    int calcBeatCrossFrequency(track* t);
    int calcAmplitudeLateralHeadDisplacement(track* t);
    int calcMeanAngularDisplacement(track* t);

    // Sample motility parameter calculation functions
    int calcAllSampleMotilityValues();
    int calcPercentMotile();
    int calcPercentImmotile();
    int calcPercentHyperactivated();
    int calcPercentRapidAndLinear();
    int calcPercentProgMotile();
    int calcPercentNonProgMotile();

    // Getters
    double getFPS() const { return fps; }
    size_t getNumTracks() const { return tracks.size(); }
    size_t getNumCoords(unsigned int trackIndex) const { return tracks[trackIndex].coords.size(); }
    size_t getNumAvgPathCoords(unsigned int trackIndex) const { return tracks[trackIndex].avgPathCoords.size(); }

    int getXCoord(unsigned int trackIndex, unsigned int coordIndex, double& x) const;
    int getYCoord(unsigned int trackIndex, unsigned int coordIndex, double& y) const;
    int getZCoord(unsigned int trackIndex, unsigned int coordIndex, double& z) const;

    int getXAvgPathCoord(unsigned int trackIndex, unsigned int coordIndex, double& x) const;
    int getYAvgPathCoord(unsigned int trackIndex, unsigned int coordIndex, double& y) const;
    int getZAvgPathCoord(unsigned int trackIndex, unsigned int coordIndex, double& z) const;

    int getCurvilinearVel(unsigned int trackIndex, double& vcl) const;
    int getStraightLineVel(unsigned int trackIndex, double& vsl) const;
    int getAvgPathVel(unsigned int trackIndex, double& vap) const;
    int getLinearity(unsigned int trackIndex, double& linearity) const;
    int getStraightness(unsigned int trackIndex, double& straightness) const;
    int getWobble(unsigned int trackIndex, double& wobble) const;
    int getBeatCrossFrequency(unsigned int trackIndex, double& bcf) const;
    int getAmplitudeLateralHeadDisplacement(unsigned int trackIndex, double& alh) const;
    int getMeanAngularDisplacement(unsigned int trackIndex, double& mad) const;

    int getPercentMotile(double& percent) const;
    int getPercentImmotile(double& percent) const;
    int getPercentHyperactivated(double& percent) const;
    int getPercentRapidAndLinear(double& percent) const;
    int getPercentProgMotile(double& percent) const;
    int getPercentNonProgMotile(double& percent) const;

    // Debugging functions
    void printTracks();
};

#endif // DATAPROCESSOR

