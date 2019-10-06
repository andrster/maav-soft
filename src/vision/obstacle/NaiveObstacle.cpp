#include <vision/obstacle/NaiveObstacle.hpp>
#include <pcl/common/distances.h>
#include <pcl/common/centroid.h>

#include <memory>

using std::vector;
using std::shared_ptr;
using Eigen::Vector3d;
using pcl::PointCloud;
using pcl::PointXYZ;
using pcl::euclideanDistance;
using pcl::CentroidPoint;

constexpr float maxPointDist = 1.3; // Maximum distance of points from zero point
constexpr float maxObstacleDist = 0.5; // Maximum distance of points from main obstacle point
constexpr size_t minPointsInObstacle = 200;

// Simple class used to bin points into obstacles
// and then retrieve the list of obstacles compiled here
class ObstaclesHolder
{
public:
    void addPoint(PointXYZ& point)
    {
        // Try to fit into new obstacles
        for (size_t i = 0; i < obstacles_.size(); ++i)
        {
            if (euclideanDistance<PointXYZ, PointXYZ>(obstacles_[i], point) < maxObstacleDist)
            {
                // centroids_[i]->add(point);
                ocurrences[i] += 1;
                return;
            }
        }
        // Could not fit into any already present obstacles, put here
        obstacles_.push_back(point);
        ocurrences.push_back(1);
        // centroids_.emplace_back();
        // centroids_.back()->add(point);
    }
    vector<Vector3d> getObstacles()
    {
        vector<Vector3d> eigenObstacles;
        eigenObstacles.reserve(obstacles_.size());
        for (size_t i = 0; i < ocurrences.size(); ++i)
        {
            auto& ocurrence = ocurrences[i];
            if (ocurrence >= minPointsInObstacle)
            {
                eigenObstacles.emplace_back(obstacles_[i].x, obstacles_[i].y, obstacles_[i].z);
            }
        }
        return eigenObstacles;
    }
private:
    vector<PointXYZ> obstacles_;
    // vector<shared_ptr<CentroidPoint<PointXYZ>>> centroids_;
    vector<size_t> ocurrences;
};

bool isDirectlyForward(PointXYZ& point)
{
    return ((point.x < 0.7 && point.y > -0.7) && (point.y < 0.3 && point.y > -0.3) && 
        point.z > 0.5);
}

vector<Vector3d> maav::vision::NaiveObstacle::detectObstacles(PointCloud<PointXYZ>::Ptr cloud)
{
    // Traverse the point cloud keeping only points that are within 1.5m of the camera
    PointXYZ zeroPoint(0, 0, 0);
    PointCloud<PointXYZ>::Ptr filteredCloud = PointCloud<PointXYZ>::Ptr(new PointCloud<PointXYZ>());
    // TODO ALSO FILTER OUT THE POINTS THAT ARE LIKELY TO BE PROP GAURDS OR ELSEWHERE ON THE VEHICLE
    for (auto& point : *cloud)
    {
        if (euclideanDistance<PointXYZ, PointXYZ>(zeroPoint, point) < maxPointDist &&
            !isOnVehicle(point) && isDirectlyForward(point))
        {
            filteredCloud->push_back(point);
        }
    }
    ObstaclesHolder obstacles;
    for (auto& point : *filteredCloud)
    {
        obstacles.addPoint(point);
    }
    return obstacles.getObstacles();
}

bool maav::vision::NaiveObstacle::isOnVehicle(PointXYZ& point)
{
    return ((point.x < 0.6 && point.y > -0.6) && (point.y < 0.5 && point.y > 0) && 
        point.z < 0.6);
}