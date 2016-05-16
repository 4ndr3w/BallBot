#ifndef VisionMessages_h
#define VisionMessages_h

#define VISIONMSG_TYPE_SYNCTS 's'
#define VISIONMSG_TYPE_UPDATE 'u'

struct VisionUpdate {
  char messageType;
  int16_t timestamp;
  int16_t theta;
  int16_t distance;
};

#endif
