#include "vision/core/PlaneFitter.hpp"

// TODO Move to a config file
// Used to filter out poor data when out of the camera's range
constexpr float NECESSARY_INLIER_PROPORTION = 0.8f;

using maav::vision::PlaneFitter;

PlaneFitter::PlaneFitter(const float inlier_threshold)
    : inlier_thresh_{inlier_threshold}, last_height_{0}, last_time_(0)
{
}

Eigen::MatrixXf PlaneFitter::fitPlane(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    // Set up pcl plane segmentation data
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZ> segs;
    // Optional
    segs.setOptimizeCoefficients(true);
    // Mandatory
    segs.setModelType(pcl::SACMODEL_PLANE);
    segs.setMethodType(pcl::SAC_RANSAC);
    segs.setDistanceThreshold(inlier_thresh_);
    // Old distanceThreshold at 0.3
    segs.setInputCloud(cloud);
    segs.setOptimizeCoefficients(true);
    // Set the cloud to use for plane fitting
    segs.setInputCloud(cloud);
    if (cloud->size())
    {
        // Beginning planar segmentation
        segs.segment(*inliers, *coefficients);
        // Check to see if a model was found
        // If no model found, return failure
        if (inliers->indices.size() < (NECESSARY_INLIER_PROPORTION * cloud->size()))
        {
            return Eigen::MatrixXf(0, 0);
        }
    }
    else  // If empty cloud was passed in, return failure
    {
        return Eigen::MatrixXf(0, 0);
    }
    if (coefficients->values.size())
    {
        Eigen::MatrixXf coefficients_matrix(4, 1);
        for (unsigned i = 0; i < 4; ++i)
        {
            coefficients_matrix(i, 0) = coefficients->values[i];
        }
        return coefficients_matrix;
    }
    return Eigen::MatrixXf(0, 0);  // No coefficients, return failure
}

bool PlaneFitter::runPlaneFitting(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, vector1_t &zdot,
    vector1_t &zdepth, vector1_t &roll, vector1_t &pitch, uint64_t utime)
{
    return getPlaneInfo(cloud, zdot, zdepth, roll, pitch, utime, junk_matrix_);
}

bool PlaneFitter::getPlaneInfo(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, vector1_t &zdot,
    vector1_t &zdepth, vector1_t &roll, vector1_t &pitch, uint64_t utime, Eigen::MatrixXf &coefs)
{
    coefs = fitPlane(cloud);
    if (coefs.size() == 0)
    {
        return false;
    }
    if (coefs(2) == 0.f)
    {
        return false;
    }
    zdepth.data[0] = abs(coefs(3) / coefs(2));
    float height = abs(coefs(2) * zdepth.data[0]);
    uint64_t dt = utime - last_time_;
    constexpr float USEC_TO_SEC = 1000000.0;
    zdot.data[0] = (height - last_height_) / static_cast<float>(dt) * USEC_TO_SEC;
    last_time_ = utime;
    last_height_ = height;
    // assuming quad plane normal is [0,0,1]
    float xq = 0, yq = 0, zq = 1;
    float xg = coefs(0);
    float yg = coefs(1);
    float zg = coefs(2);
    roll.data[0] = acos(((xg * xq) + (zg * zq)) / sqrt((xg * xg) + (zg * zg)));
    pitch.data[0] = acos(((yg * yq) + (zg * zq)) / sqrt((yg * yg) + (zg * zg)));
    if (yg < 0) pitch.data[0] *= -1;
    if (xg < 0) roll.data[0] *= -1;
    return true;
}
