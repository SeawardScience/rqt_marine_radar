#ifndef RQT_MARINE_RADAR_MARINE_RADAR_PLUGIN_H
#define RQT_MARINE_RADAR_MARINE_RADAR_PLUGIN_H

#include <rqt_gui_cpp/plugin.h>
#include <ui_marine_radar_plugin.h>
#include <rclcpp/rclcpp.hpp>
#include <rcl/rcl.h>
#include <marine_sensor_msgs/msg/radar_sector.hpp>
#include <marine_radar_control_msgs/msg/radar_control_set.hpp>
#include <marine_radar_control_msgs/msg/radar_control_value.hpp>
#include <mutex>

using std::placeholders::_1;

class QLabel;

namespace rqt_marine_radar
{
    
class MarineRadarPlugin: public rqt_gui_cpp::Plugin
{
    Q_OBJECT
public:
    MarineRadarPlugin();
    
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);
    
protected slots:
    virtual void updateTopicList();
    
    virtual void selectTopic(const QString& topic);  

    virtual void onTopicChanged(int index);
    virtual void onShowControlsPushButtonClicked();
    virtual void onShowRadarPushButtonClicked();
    virtual void onFadePeriodDoubleSpinBoxValueChanged();
  
    virtual void dataCallback(const marine_sensor_msgs::msg::RadarSector::ConstSharedPtr& msg);
    virtual void stateCallback(const marine_radar_control_msgs::msg::RadarControlSet::ConstSharedPtr& msg); 
  
    void updateState();
  
private:
    Ui::MarineRadarWidget m_ui;
    QWidget* m_widget;
    rclcpp::Subscription<marine_sensor_msgs::msg::RadarSector>::ConstSharedPtr m_dataSubscriber;
    rclcpp::Subscription<marine_radar_control_msgs::msg::RadarControlSet>::ConstSharedPtr m_stateSubscriber;
    rclcpp::Publisher<marine_radar_control_msgs::msg::RadarControlValue>::SharedPtr m_stateChangePublisher;

    QString m_arg_topic;
    
    struct ControlSet
    {
        QLabel *label;
        QLabel *state;
        QWidget *input;
    };
    
    std::map<std::string,ControlSet> m_controls;
    std::vector<QMetaObject::Connection> m_connections;
    
    std::vector<marine_radar_control_msgs::msg::RadarControlItem> m_new_state;
    std::mutex m_state_mutex;
};

} // namespace rqt_marine_radar

#endif
