#include "cinder/Cinder.h"
#include "cinder/Channel.h"
#include "cinder/Function.h"

namespace Kinect
{
    typedef std::shared_ptr<struct Device> DeviceRef;

    struct Device
    {
        struct Option
        {
            Option()
            {
                enableColor = false;
                enableDepth = true;
                enableBody = false;
                enableBodyIndex = false;
                enableInfra = false;
                enableAudio = false;
            }
            bool enableColor;
            bool enableDepth;
            bool enableBody;
            bool enableBodyIndex;
            bool enableInfra;
            bool enableAudio;
        };
        Option option;

#ifdef KINECT_V2
        static DeviceRef createV2(Option option = Option());
#else
        static DeviceRef createV1(Option option = Option());
#endif

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        ci::Channel16u depthChannel;
        ci::signals::signal<void()> signalDepthDirty;

        struct Body
        {
            ci::uint64_t id;
            ci::vec3 pos3d;
            ci::vec2 pos2d;

            enum JointType
            {
                LEFT_HAND,
                RIGHT_HAND,
                HEAD,
                JOINT_COUNT,
            };

            struct Joint
            {
                ci::vec3 pos3d;
                ci::vec2 pos2d;
                float confidence;
            };

            Joint joints[JOINT_COUNT];
        };
        std::vector<Body> bodies;
        ci::signals::signal<void()> signalBodyDirty;
    };
}
