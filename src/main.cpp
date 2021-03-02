#include "ros/ros.h"
#include "std_msgs/String.h"

extern "C" {
#include "lcd1602.h"
}

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    lcd1602Clear();

    const std::string& message = msg->data;
    std::size_t crlf = message.find('\n');

    lcd1602SetCursor(0,0);

    if (crlf != std::string::npos) { // two lines
	lcd1602WriteString ((char*)message.substr(0, crlf).c_str());
	lcd1602SetCursor(0,1);
	lcd1602WriteString ((char*)message.substr(crlf+1, crlf+17).c_str());	
    } else { // one line
	lcd1602WriteString ((char*)message.substr(0,16).c_str());
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lcd1602");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("lcd1602", 1000, chatterCallback);

  int rc = lcd1602Init(0, 0x27);
  if (rc) {
      ROS_ERROR("Failed to initialize LCD1602");
      return -1;
  }
  lcd1602Clear();
  lcd1602SetCursor(0,0);
  lcd1602Control(1,0,0);  

  ros::spin();

  lcd1602Clear();
  lcd1602Shutdown();
  return 0;
}
