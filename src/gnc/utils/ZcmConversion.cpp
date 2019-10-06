#include <gnc/utils/ZcmConversion.hpp>

#include <algorithm>
#include <vector>

using maav::gnc::measurements::GlobalUpdateMeasurement;
using maav::gnc::measurements::ImuMeasurement;
using maav::gnc::measurements::LidarMeasurement;
using maav::gnc::measurements::PlaneFitMeasurement;

namespace maav
{
namespace gnc
{
vector1_t convertVector1d(double vec)
{
    vector1_t new_vec;
    new_vec.data[0] = vec;
    return new_vec;
}

double convertVector1d(const vector1_t& zcm_vec) { return zcm_vec.data[0]; }

vector2_t convertVector2d(const Eigen::Vector2d& vec)
{
    vector2_t new_vec;
    new_vec.data[0] = vec.x();
    new_vec.data[1] = vec.y();
    return new_vec;
}
Eigen::Vector2d convertVector2d(const vector2_t& zcm_vec)
{
    Eigen::Vector2d vec;
    vec.x() = zcm_vec.data[0];
    vec.y() = zcm_vec.data[1];
    return vec;
}

vector3_t convertVector3d(const Eigen::Vector3d& vec)
{
    vector3_t zcm_vec;
    zcm_vec.data[0] = vec.x();
    zcm_vec.data[1] = vec.y();
    zcm_vec.data[2] = vec.z();
    return zcm_vec;
}

Eigen::Vector3d convertVector3d(const vector3_t& zcm_vec)
{
    Eigen::Vector3d vec;
    vec.x() = zcm_vec.data[0];
    vec.y() = zcm_vec.data[1];
    vec.z() = zcm_vec.data[2];
    return vec;
}

vector4_t convertVector4d(const Eigen::Vector4d& vec)
{
    vector4_t zcm_vec;
    zcm_vec.data[0] = vec.w();
    zcm_vec.data[1] = vec.x();
    zcm_vec.data[2] = vec.y();
    zcm_vec.data[3] = vec.z();
    return zcm_vec;
}

Eigen::Vector4d convertVector4d(const vector4_t& zcm_vec)
{
    Eigen::Vector4d vec;
    vec.w() = zcm_vec.data[0];
    vec.x() = zcm_vec.data[1];
    vec.y() = zcm_vec.data[2];
    vec.z() = zcm_vec.data[3];
    return vec;
}

quaternion_t convertQuaternion(const Sophus::SO3d& att)
{
    quaternion_t zcm_quat;
    const Eigen::Quaterniond& quat = att.unit_quaternion();
    zcm_quat.data[0] = quat.w();
    zcm_quat.data[1] = quat.x();
    zcm_quat.data[2] = quat.y();
    zcm_quat.data[3] = quat.z();
    return zcm_quat;
}

Sophus::SO3d convertQuaternion(const quaternion_t& zcm_att)
{
    Eigen::Quaterniond quat;
    quat.w() = zcm_att.data[0];
    quat.x() = zcm_att.data[1];
    quat.y() = zcm_att.data[2];
    quat.z() = zcm_att.data[3];
    return Sophus::SO3d(quat);
}

void convertPose(const Sophus::SE3d& pose, quaternion_t& rotation, vector3_t& position)
{
    rotation = convertQuaternion(pose.so3());
    position = convertVector3d(pose.translation());
}

Sophus::SE3d convertPose(const quaternion_t& rotation, const vector3_t& position)
{
    Sophus::SE3d pose;
    pose.so3() = convertQuaternion(rotation);
    pose.translation() = convertVector3d(position);
    return pose;
}

state_t ConvertState(const State& state)
{
    state_t zcm_state;
    zcm_state.utime = state.timeUSec();

    zcm_state.attitude = convertQuaternion(state.attitude());
    zcm_state.position = convertVector3d(state.position());
    zcm_state.velocity = convertVector3d(state.velocity());
    zcm_state.angular_velocity = convertVector3d(state.angularVelocity());
    zcm_state.acceleration = convertVector3d(state.acceleration());
    zcm_state.magnetic_field = convertVector3d(state.magneticFieldVector());
    zcm_state.gravity = convertVector3d(state.gravity());
    zcm_state.gyro_biases = convertVector3d(state.gyroBias());
    zcm_state.accel_biases = convertVector3d(state.accelBias());
    convertMatrix(state.covariance(), zcm_state.covariance);

    return zcm_state;
}

State ConvertState(const state_t& zcm_state)
{
    State state(zcm_state.utime);

    state.attitude() = convertQuaternion(zcm_state.attitude);
    state.position() = convertVector3d(zcm_state.position);
    state.velocity() = convertVector3d(zcm_state.velocity);
    state.gyroBias() = convertVector3d(zcm_state.gyro_biases);
    state.accelBias() = convertVector3d(zcm_state.accel_biases);
    state.angularVelocity() = convertVector3d(zcm_state.angular_velocity);
    state.acceleration() = convertVector3d(zcm_state.acceleration);
    state.magneticFieldVector() = convertVector3d(zcm_state.magnetic_field);
    state.gravity() = convertVector3d(zcm_state.gravity);
    convertMatrix(state.covariance(), zcm_state.covariance);

    return state;
}

State ConvertGroundTruthState(const groundtruth_inertial_t& zcm_state)
{
    State state(zcm_state.utime);

    state.attitude() = convertQuaternion(zcm_state.attitude);
    state.position() = convertVector3d(zcm_state.position);
    state.velocity() = convertVector3d(zcm_state.velocity);
    state.angularVelocity() = convertVector3d(zcm_state.angular_velocity);
    state.acceleration() = convertVector3d(zcm_state.acceleration);

    return state;
}

// TODO: what is rate[3] supposed to be??
waypoint_t ConvertWaypoint(const Waypoint& waypoint)
{
    waypoint_t zcm_waypoint;

    zcm_waypoint.pose[0] = waypoint.position[0];
    zcm_waypoint.pose[1] = waypoint.position[1];
    zcm_waypoint.pose[2] = waypoint.position[2];
    zcm_waypoint.pose[3] = waypoint.yaw;

    zcm_waypoint.rate[0] = waypoint.velocity[0];
    zcm_waypoint.rate[1] = waypoint.velocity[1];
    zcm_waypoint.rate[2] = waypoint.velocity[2];
    zcm_waypoint.rate[3] = waypoint.yaw_rate;

    return zcm_waypoint;
}

Waypoint ConvertWaypoint(const waypoint_t& zcm_waypoint)
{
    Waypoint waypoint;
    waypoint.position =
        Eigen::Vector3d(zcm_waypoint.pose[0], zcm_waypoint.pose[1], zcm_waypoint.pose[2]);
    waypoint.velocity =
        Eigen::Vector3d(zcm_waypoint.rate[0], zcm_waypoint.rate[1], zcm_waypoint.rate[2]);
    waypoint.yaw = zcm_waypoint.pose[3];

    return waypoint;
}

path_t ConvertPath(const Path& path)
{
    path_t zcm_path;
    zcm_path.utime = path.utime;
    zcm_path.NUM_WAYPOINTS = path.waypoints.size();
    std::transform(path.waypoints.cbegin(), path.waypoints.cend(),
        std::back_inserter(zcm_path.waypoints),
        [](const Waypoint& elt) { return ConvertWaypoint(elt); });
    return zcm_path;
}

Path ConvertPath(const path_t& zcm_path)
{
    Path path;
    path.utime = zcm_path.utime;
    std::transform(zcm_path.waypoints.cbegin(), zcm_path.waypoints.cend(),
        std::back_inserter(path.waypoints),
        [](const waypoint_t& elt) { return ConvertWaypoint(elt); });
    return path;
}

std::shared_ptr<LidarMeasurement> convertLidar(const lidar_t& zcm_lidar)
{
    std::shared_ptr<LidarMeasurement> lidar(new LidarMeasurement());

    lidar->distance()(0) = convertVector1d(zcm_lidar.distance);
    lidar->setTime(zcm_lidar.utime);

    return lidar;
}

// lidar_t convertLidar(const measurements::LidarMeasurement& lidar)
// {
//     lidar_t zcm_lidar;
//     zcm_lidar.distance = lidar.distance()(0);
//     zcm_lidar.utime = lidar.timeUSec();
//     return zcm_lidar;
// }

std::shared_ptr<ImuMeasurement> convertImu(const imu_t& zcm_imu)
{
    std::shared_ptr<ImuMeasurement> imu(new ImuMeasurement);

    imu->time_usec = zcm_imu.utime;

    imu->acceleration = convertVector3d(zcm_imu.acceleration);
    imu->angular_rates = convertVector3d(zcm_imu.angular_rates);
    imu->magnetometer = convertVector3d(zcm_imu.magnetometer);

    return imu;
}

std::shared_ptr<PlaneFitMeasurement> convertPlaneFit(const plane_fit_t& zcm_plane_fit)
{
    std::shared_ptr<PlaneFitMeasurement> plane_fit(new PlaneFitMeasurement());

    plane_fit->time_usec = zcm_plane_fit.utime;

    plane_fit->height = convertVector1d(zcm_plane_fit.z);
    plane_fit->vertical_speed = convertVector1d(zcm_plane_fit.z_dot);

    plane_fit->roll = convertVector1d(zcm_plane_fit.roll);
    plane_fit->pitch = convertVector1d(zcm_plane_fit.pitch);

    return plane_fit;
}

std::shared_ptr<GlobalUpdateMeasurement> convertGlobalUpdate(const global_update_t& zcm_global)
{
    std::shared_ptr<GlobalUpdateMeasurement> global_update(new GlobalUpdateMeasurement());

    global_update->setTime(zcm_global.utime);
    global_update->pose() = convertPose(zcm_global.attitude, zcm_global.position);

    return global_update;
}

control::Controller::Parameters convertControlParams(const ctrl_params_t& ctrl_params)
{
    using Params = control::Controller::Parameters;
    Params converted_params;

    // Copy position gains
    converted_params.pos_gains[Params::X][Params::P] = ctrl_params.value[Params::X].p;
    converted_params.pos_gains[Params::X][Params::I] = ctrl_params.value[Params::X].i;
    converted_params.pos_gains[Params::X][Params::D] = ctrl_params.value[Params::X].d;

    converted_params.pos_gains[Params::Y][Params::P] = ctrl_params.value[Params::Y].p;
    converted_params.pos_gains[Params::Y][Params::I] = ctrl_params.value[Params::Y].i;
    converted_params.pos_gains[Params::Y][Params::D] = ctrl_params.value[Params::Y].d;

    converted_params.pos_gains[Params::Z][Params::P] = ctrl_params.value[Params::Z].p;
    converted_params.pos_gains[Params::Z][Params::I] = ctrl_params.value[Params::Z].i;
    converted_params.pos_gains[Params::Z][Params::D] = ctrl_params.value[Params::Z].d;

    // Copy rate gains
    converted_params.rate_gains[Params::DX][Params::P] = ctrl_params.rate[Params::DX].p;
    converted_params.rate_gains[Params::DX][Params::I] = ctrl_params.rate[Params::DX].i;
    converted_params.rate_gains[Params::DX][Params::D] = ctrl_params.rate[Params::DX].d;

    converted_params.rate_gains[Params::DY][Params::P] = ctrl_params.rate[Params::DY].p;
    converted_params.rate_gains[Params::DY][Params::I] = ctrl_params.rate[Params::DY].i;
    converted_params.rate_gains[Params::DY][Params::D] = ctrl_params.rate[Params::DY].d;

    converted_params.rate_gains[Params::DZ][Params::P] = ctrl_params.rate[Params::DZ].p;
    converted_params.rate_gains[Params::DZ][Params::I] = ctrl_params.rate[Params::DZ].i;
    converted_params.rate_gains[Params::DZ][Params::D] = ctrl_params.rate[Params::DZ].d;

    converted_params.rate_gains[Params::DYAW][Params::P] = ctrl_params.rate[Params::DYAW].p;
    converted_params.rate_gains[Params::DYAW][Params::I] = ctrl_params.rate[Params::DYAW].i;
    converted_params.rate_gains[Params::DYAW][Params::D] = ctrl_params.rate[Params::DYAW].d;

    converted_params.angle_limits[0] = {ctrl_params.roll_limits[0], ctrl_params.roll_limits[1]};
    converted_params.angle_limits[1] = {ctrl_params.pitch_limits[0], ctrl_params.pitch_limits[1]};

    return converted_params;
}

}  // namespace gnc
}  // namespace maav
