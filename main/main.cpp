#include <ebli.h>
#include <ebli_events.h>
#include <esp_log.h>
#include <Sensors.h>
#include <PowerManager.h>

#define SLEEP_TIME_IN_SECONDS 10

static void readAndPublishSensorsAndWaitAndSleep()
{
    ESP_LOGI("APP", "read Sensors");
    EBLi::Sensors::Sensors::publishAll();

    ESP_LOGI("APP", "wait a sec");
    // wait one second to give sensors time to finish its job
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ESP_LOGI("APP", "request sleep");
    auto pm = EBLi::Power::PowerManager::instance();
    pm->requestWakeupIn(SLEEP_TIME_IN_SECONDS * 1000);
}

static void onEbliMqttConnected(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ESP_LOGI("APP", "onEbliMqttConnected");
    readAndPublishSensorsAndWaitAndSleep();
}

#ifdef __cplusplus
extern "C" {
#endif

void app_main()
{
    EBLi::init_all();

    ESP_ERROR_CHECK(esp_event_handler_register(EBLI_EVENTS, EBLI_EVENT_MQTT_CONNECTED, onEbliMqttConnected, nullptr));

    readAndPublishSensorsAndWaitAndSleep();
}

#ifdef __cplusplus
} // extern "C"
#endif
