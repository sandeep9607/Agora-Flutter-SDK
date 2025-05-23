
#pragma once

#include "iris_rtc_c_api.h"

struct IrisSpatialAudioZone {
  //the zone id
  int zoneSetId;
  //zone center point
  float position[3];
  //forward direction
  float forward[3];
  //right direction
  float right[3];
  //up direction
  float up[3];
  //the forward side length of the zone
  float forwardLength;
  //tehe right side length of the zone
  float rightLength;
  //the up side length of the zone
  float upLength;
  //the audio attenuation of zone
  float audioAttenuation;
};

struct IrisAudioFrame {
  //The audio frame type: #AUDIO_FRAME_TYPE.
  int type;
  //The number of samples per channel in this frame.
  int samplesPerChannel;
  //The number of bytes per sample: #BYTES_PER_SAMPLE
  int bytesPerSample;
  //The number of audio channels (data is interleaved, if stereo).
  int channels;
  //The sample rate
  int samplesPerSec;
  //The data buffer of the audio frame. When the audio frame uses a stereo channel, the data buffer is interleaved.
  void *buffer;
  // The timestamp to render the audio data.
  int64_t renderTimeMs;
  // A reserved parameter.
  int avsync_type;
  // The pts timestamp of this audio frame.
  int64_t presentationMs;
  // The number of the audio track.
  int audioTrackNumber;
  // RTP timestamp of the first sample in the audio frame
  uint32_t rtpTimestamp;
};

struct IrisHdr10MetadataInfo {
  //The x coordinates of the red value in the CIE1931 color space. The values need to normalized to 50,000.
  uint16_t redPrimaryX;
  // The y coordinates of the red value in the CIE1931 color space. The values need to normalized to 50,000.
  uint16_t redPrimaryY;
  // The x coordinates of the green value in the CIE1931 color space. The values need to normalized to 50,000.
  uint16_t greenPrimaryX;
  // The y coordinates of the green value in the CIE1931 color space. The values need to normalized to 50,000.
  uint16_t greenPrimaryY;
  // The x coordinates of the blue value in the CIE1931 color space. The values need to normalized to 50,000.
  uint16_t bluePrimaryX;
  // The y coordinates of the blue value in the CIE1931 color space. The values need to normalized to 50,000.
  uint16_t bluePrimaryY;
  // The x coordinates of the white point in the CIE1931 color space.The values need to normalized to 50,000.
  uint16_t whitePointX;
  // The y coordinates of the white point in the CIE1931 color space.The values need to normalized to 50,000.
  uint16_t whitePointY;
  // The maximum number of nits of the display used to master the content. The values need to normalized to 10,000.
  unsigned int maxMasteringLuminance;
  // The minimum number of nits of the display used to master the content. The values need to normalized to 10,000.
  unsigned int minMasteringLuminance;
  // The maximum content light level (MaxCLL). This is the nit value corresponding to the brightest pixel used anywhere in the content.
  uint16_t maxContentLightLevel;
  // The maximum frame average light level (MaxFALL). This is the nit value corresponding to the average luminance of the frame which has the brightest average luminance anywhere in the content.
  uint16_t maxFrameAverageLightLevel;
};

struct IrisColorSpace {
  int primaries;
  int transfer;
  int matrix;
  int range;
};

struct IrisExternalVideoFrame {
  //The buffer type: #VIDEO_BUFFER_TYPE.
  int type;
  // The pixel format: #VIDEO_PIXEL_FORMAT
  int format;
  // The video buffer.
  void *buffer;
  // The line spacing of the incoming video frame (px). For texture, it is the width of the texture.
  int stride;
  // The height of the incoming video frame.
  int height;
  // [Raw data related parameter] The number of pixels trimmed from the left. The default value is 0.
  int cropLeft;
  // [Raw data related parameter] The number of pixels trimmed from the top. The default value is 0.
  int cropTop;
  //[Raw data related parameter] The number of pixels trimmed from the right. The default value is
  int cropRight;
  // [Raw data related parameter] The number of pixels trimmed from the bottom. The default value
  int cropBottom;
  // [Raw data related parameter] The clockwise rotation information of the video frame. You can set the
  // rotation angle as 0, 90, 180, or 270. The default value is 0.
  int rotation;
  // The timestamp (ms) of the incoming video frame. An incorrect timestamp results in a frame loss or
  // unsynchronized audio and video.
  long long timestamp;
  // [Texture-related parameter]
  // When using the OpenGL interface (javax.microedition.khronos.egl.*) defined by Khronos, set EGLContext to this field.
  // When using the OpenGL interface (android.opengl.*) defined by Android, set EGLContext to this field.
  void *eglContext;
  // [Texture related parameter] Texture ID used by the video frame.
  int eglType;
  // [Texture related parameter] Incoming 4 &times; 4 transformational matrix. The typical value is a unit matrix.
  int textureId;
  /**
   * [Texture related parameter] The fence object related to the textureId parameter, indicating the synchronization status of the video data in Texture format.
   * The default value is 0
   */
  long long fenceObject;
  // [Texture related parameter] Incoming 4 &times; 4 transformational matrix. The typical value is a unit matrix.
  float matrix[16];
  // [Texture related parameter] The MetaData buffer. The default value is NULL
  uint8_t *metadataBuffer;
  // [Texture related parameter] The MetaData size.The default value is 0
  int metadataSize;
  //  Indicates the alpha channel of current frame, which is consistent with the dimension of the video frame.
  uint8_t *alphaBuffer;
  //  Extract alphaBuffer from bgra or rgba data. Set it true if you do not explicitly specify the alphabuffer.
  bool fillAlphaBuffer;
  /**
   *  The relative position between alphabuffer and the frame.
   *  0: Normal frame;
   *  1: Alphabuffer is above the frame;
   *  2: Alphabuffer is below the frame;
   *  3: Alphabuffer is on the left of frame;
   *  4: Alphabuffer is on the right of frame;
   *  The default value is 0.
   */
  int alphaStitchMode;
  //[For Windows only] The pointer of ID3D11Texture2D used by the video frame.
  void *d3d11Texture2d;
  // [For Windows only] The index of ID3D11Texture2D array used by the video frame.
  int textureSliceIndex;
  // metadata info used for hdr video data
  IrisHdr10MetadataInfo hdr10MetadataInfo;
  // The ColorSpace of the video frame.
  IrisColorSpace colorSpace;
};

struct IrisEncodedVideoFrameInfo {
  // ID of the user that pushes the the external encoded video frame..
  unsigned int uid;
  // The codec type of the local video stream. See #VIDEO_CODEC_TYPE. The default value is `VIDEO_CODEC_H265 (3)`.
  int codecType;
  // The width (px) of the video frame.
  int width;
  // The height (px) of the video frame.
  int height;
  // The number of video frames per second.
  int framesPerSecond;
  // The video frame type: #VIDEO_FRAME_TYPE.
  int frameType;
  // The rotation information of the video frame: #VIDEO_ORIENTATION.
  int rotation;
  // The track ID of the video frame.
  int trackId;
  // This is a input parameter which means the timestamp for capturing the video.
  int64_t captureTimeMs;
  // The timestamp for decoding the video.
  int64_t decodeTimeMs;
  // The stream type of video frame.
  int streamType;
  // @technical preview
  int64_t presentationMs;
};

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_SetMaxAudioRecvCount(
    IrisHandle enginePtr, int maxCount);

IRIS_API int IRIS_CALL
ILocalSpatialAudioEngine_SetAudioRecvRange(IrisHandle enginePtr, float range);

IRIS_API int IRIS_CALL
ILocalSpatialAudioEngine_SetDistanceUnit(IrisHandle enginePtr, float unit);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_UpdateSelfPosition(
    IrisHandle enginePtr, float positionX, float positionY, float positionZ,
    float axisForwardX, float axisForwardY, float axisForwardZ,
    float axisRightX, float axisRightY, float axisRightZ, float axisUpX,
    float axisUpY, float axisUpZ);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_UpdateSelfPositionEx(
    IrisHandle enginePtr, float positionX, float positionY, float positionZ,
    float axisForwardX, float axisForwardY, float axisForwardZ,
    float axisRightX, float axisRightY, float axisRightZ, float axisUpX,
    float axisUpY, float axisUpZ, const char *channelId, unsigned int localUid);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_UpdatePlayerPositionInfo(
    IrisHandle enginePtr, int playerId, float positionX, float positionY,
    float positionZ, float forwardX, float forwardY, float forwardZ);

IRIS_API int IRIS_CALL
ILocalSpatialAudioEngine_MuteLocalAudioStream(IrisHandle enginePtr, bool mute);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_MuteAllRemoteAudioStreams(
    IrisHandle enginePtr, bool mute);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_SetZones(
    IrisHandle enginePtr, IrisSpatialAudioZone *zones, unsigned int zoneCount);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_SetPlayerAttenuation(
    IrisHandle enginePtr, int playerId, double attenuation, bool forceSet);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_MuteRemoteAudioStream(
    IrisHandle enginePtr, unsigned int uid, bool mute);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_UpdateRemotePosition(
    IrisHandle enginePtr, unsigned int uid, float positionX, float positionY,
    float positionZ, float forwardX, float forwardY, float forwardZ);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_UpdateRemotePositionEx(
    IrisHandle enginePtr, unsigned int uid, float positionX, float positionY,
    float positionZ, float forwardX, float forwardY, float forwardZ,
    const char *channelId, unsigned int localUid);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_RemoveRemotePosition(
    IrisHandle enginePtr, unsigned int uid);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_RemoveRemotePositionEx(
    IrisHandle enginePtr, unsigned int uid, const char *channelId,
    unsigned int localUid);

IRIS_API int IRIS_CALL
ILocalSpatialAudioEngine_ClearRemotePositions(IrisHandle enginePtr);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_ClearRemotePositionsEx(
    IrisHandle enginePtr, const char *channelId, unsigned int localUid);

IRIS_API int IRIS_CALL ILocalSpatialAudioEngine_SetRemoteAudioAttenuation(
    IrisHandle enginePtr, unsigned int uid, double attenuation, bool forceSet);

IRIS_API int IRIS_CALL IMediaEngine_PushAudioFrame(IrisHandle enginePtr,
                                                   IrisAudioFrame *frame,
                                                   unsigned int trackId);

IRIS_API int IRIS_CALL IMediaEngine_PullAudioFrame(IrisHandle enginePtr,
                                                   IrisAudioFrame *frame);

IRIS_API int IRIS_CALL
IMediaEngine_PushVideoFrame(IrisHandle enginePtr, IrisExternalVideoFrame *frame,
                            unsigned int videoTrackId);

IRIS_API int IRIS_CALL IMediaEngine_PushEncodedVideoImage(
    IrisHandle enginePtr, const unsigned char *imageBuffer,
    unsigned long long length, IrisEncodedVideoFrameInfo &videoEncodedFrameInfo,
    unsigned int videoTrackId);