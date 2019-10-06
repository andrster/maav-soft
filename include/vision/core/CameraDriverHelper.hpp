#ifndef CAMERA_DRIVER_H
#define CAMERA_DRIVER_H

#include <chrono>
#include <string>
#include <thread>

#include <yaml-cpp/yaml.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zcm/zcm-cpp.hpp>

#include <common/messages/rgbd_image_t.hpp>
#include <vision/core/D400CameraInterface.hpp>

namespace maav::vision
{
class CameraDriverHelper
{
public:
    CameraDriverHelper() = delete;

    CameraDriverHelper(YAML::Node config, const std::string& zcm_format,
        const std::string& rgbd_channel_in,
        const std::string& pointcloud_channel_in,
        const std::string& pos_channel_in);

    ~CameraDriverHelper() { endRecording(); }

    void beginRecording();

    void endRecording();

    bool isRunning() { return running_; }

    static const std::string FORMAT_IPC;

private:
    bool enabled_;
    bool publish_rgbd_;
    bool publish_pc_;
    bool publish_pose_; // TODO usage in impl
    bool autoexposure_;
    zcm::ZCM zcm_;
    maav::vision::D400CameraInterface camera_;
    bool running_;
    std::thread publish_thread_;
    std::string rgbd_channel_;
    std::string pointcloud_channel_;
    std::string pose_channel_;// TODO using in impl
    // TODO ZCM message type for pos data

    void publish();
    void rgbdPublish();
    void pointcloudPublish();
    void posPublish();
};
}  // namespace maav::vision

#endif
