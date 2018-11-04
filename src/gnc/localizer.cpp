#include "gnc/localizer.hpp"
#include "gnc/state/base_state.hpp"

using namespace cv;

namespace maav
{
namespace gnc
{
Localizer::Localizer(SlamInitializer& slam_init)
    : slam(slam_init.vocabulary_file, slam_init.config_file, slam_init.sensor, slam_init.use_viewer)
{
}

Localizer::~Localizer() { slam.Shutdown(); }
void Localizer::add_image(const Mat& color, const Mat& depth, uint64_t timestamp)
{
    constexpr double MICROSECONDS_PER_SECOND = 1000000;
    double seconds = static_cast<double>(timestamp) / MICROSECONDS_PER_SECOND;
    slam.TrackRGBD(color, depth, seconds);
}

void Localizer::add_imu(/*const measurements::ImuMeasurement& imu*/)
{
    // TODO: IMU frontend + On Manifold Preintegration + Bias
}

}  // namespace gnc
}  // namespace maav