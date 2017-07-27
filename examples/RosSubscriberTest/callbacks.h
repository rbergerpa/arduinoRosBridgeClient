const int STR_SIZE = 128;
template<typename MsgT>
void integerCallback(const MsgT& msg) {
  char str[STR_SIZE];
  char buf[16];

  strncpy(str, "Callback msgType:  ", STR_SIZE);
  strncat(str, ((ros::Msg*) &msg)->getType(), STR_SIZE);
  strncat(str, " ", STR_SIZE);

  strncat(str, itoa(msg.data, buf, 10), STR_SIZE);

  nh.loginfo(str);
 }
template<typename MsgT>
inline void floatArrayCallback(const MsgT& msg) {
  char str[STR_SIZE];
  char buf[16];

  strncpy(str, "Callback msgType:  ", STR_SIZE);
  strncat(str, ((ros::Msg*) &msg)->getType(), STR_SIZE);
  strncat(str, " ", STR_SIZE);

  for (int i = 0; i < msg.data_length; i++) {
    dtostrf(msg.data[i], 5, 2, buf);
    strncat(str, buf, STR_SIZE);
    strncat(str, " ", STR_SIZE);
  }

  nh.loginfo(str);
 }

template<typename MsgT>
void integerArrayCallback(const MsgT& msg) {
  char str[STR_SIZE];
  char buf[16];

  strncpy(str, "Callback msgType:  ", STR_SIZE);
  strncat(str, ((ros::Msg*) &msg)->getType(), STR_SIZE);
  strncat(str, " ", STR_SIZE);

  for (int i = 0; i < msg.data_length; i++) {
    strncat(str, itoa(msg.data[i], buf, 10), STR_SIZE);
    strncat(str, " ", STR_SIZE);
  }

  nh.loginfo(str);
 }
