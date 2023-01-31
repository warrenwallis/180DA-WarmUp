import paho.mqtt.client as mqtt
import numpy as np
import time

def mqtt_publisher():
    # 0. define callbacks - functions that run when events happen.
    # The callback for when the client receives a CONNACK response from the server.
    user_gesture = 0

    def choose(rival):
        comp_gesture = rival
        mapping = {0 : 'Rock', 1 : 'Paper', 2 : 'Scissors'}
        
        if user_gesture == (comp_gesture-1)%3:
            print(f'Rival chooses {mapping[comp_gesture]}; Rival wins!')
        elif comp_gesture == (user_gesture-1)%3:
            print(f'Rival chooses {mapping[comp_gesture]}; You win!')
        else:
            print(f'Rival chooses {mapping[comp_gesture]}; Tie!')

    def on_connect(client, userdata, flags, rc):
        print("Connection returned result: " + str(rc))
        # Subscribing in on_connect() means that if we lose the connection and
        # reconnect then subscriptions will be renewed.
        client.subscribe("ece180d/zeid_rps")
        # The callback of the client when it disconnects.

    def on_disconnect(client, userdata, rc):
        if rc != 0:
            print('Unexpected Disconnect')
        else:
            print('Expected Disconnect')
        # The default message callback.
        # (won't be used if only publishing, but can still exist)

    def on_message(client, userdata, message):
        curr = int(str(message.payload)[2:-1])
        choose(curr)
        user_gesture = int(input('Input 0 for Rock, 1 for Paper, 2 for Scissors: '))
        client.publish("ece180d/warren_rps", curr, qos=1)
                
    # 1. create a client instance.
    client = mqtt.Client()
    # add additional client options (security, certifications, etc.)
    # many default options should be good to start off.
    # add callbacks to client.
    client.on_connect = on_connect
    client.on_disconnect = on_disconnect
    client.on_message = on_message

    # 2. connect to a broker using one of the connect*() functions.
    # client.connect_async("test.mosquitto.org")
    client.connect_async('mqtt.eclipseprojects.io')

    # 3. call one of the loop*() functions to maintain network traffic flow with the broker.
    client.loop_start()
    # 4. use subscribe() to subscribe to a topic and receive messages.
    # 5. use publish() to publish messages to the broker.
    # payload must be a string, bytearray, int, float or None.
    user_gesture = int(input('Input 0 for Rock, 1 for Paper, 2 for Scissors: '))
    client.publish("ece180d/warren_rps", user_gesture, qos=1)

    while True:
        pass
    # 6. use disconnect() to disconnect from the broker.
    client.loop_stop()
    client.disconnect()

def main():
    mqtt_publisher()

if __name__ == '__main__':
    main()