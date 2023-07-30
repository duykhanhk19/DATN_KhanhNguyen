import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.metrics import mean_squared_error
import socket
import json

def getTrainData():
    N = 9
    dfs = []
    for i in range(1,N,1):
        df = pd.read_csv('./data/' + str(i) + '.csv', sep=';', header=None)
        df. columns = df. iloc[0]
        df = df. tail(-1)
        df.iloc[:, :-1] = df.iloc[:, :-1].applymap(float)
        df.drop('provider', inplace=True, axis=1)
        df.drop('altitude', inplace=True, axis=1)
        df.drop('accuracy', inplace=True, axis=1)
        df = df.reset_index(drop=True)
        for j in range(1, len(df['time_millis']), 1):
            df['time_millis'][j] = (df['time_millis'][j] - df['time_millis'][0]) / 1000
        df['time_millis'][0] = 0
        dfs.append(df)
    return pd.concat(dfs)

def getTestData():
    N = 9
    df1 = pd.read_csv('./data/' + str(N) + '.csv', sep=';', header=None)
    df1. columns = df1. iloc[0]
    df1 = df1. tail(-1)
    df1.iloc[:, :-1] = df1.iloc[:, :-1].applymap(float)
    df1.drop('provider', inplace=True, axis=1)
    df1.drop('altitude', inplace=True, axis=1)
    df1.drop('accuracy', inplace=True, axis=1)
    df1 = df1.reset_index(drop=True)
    for j in range(1, len(df1['time_millis']), 1):
        df1['time_millis'][j] = (df1['time_millis'][j] - df1['time_millis'][0]) / 1000
    df1['time_millis'][0] = 0
    return df1

df_train = getTrainData()
df_test = getTestData()

x_train = df_train.drop(['time_millis'], axis=1)
y_train = np.array([i for i in df_train['time_millis']])
y_train = y_train.reshape(-1,1)

x_test = df_test.drop(['time_millis'], axis=1)
y_test = np.array([i for i in df_test['time_millis']])
y_test = y_test.reshape(-1,1)

scalerX = MinMaxScaler()
x_train = scalerX.fit_transform(x_train)
x_test = scalerX.transform(x_test)

scalerY = MinMaxScaler()
y_train = scalerY.fit_transform(y_train)

regressor = GradientBoostingRegressor(n_estimators=100, learning_rate=0.1, max_depth=3, random_state=42)
regressor.fit(x_train, y_train.ravel())

def handle_client(client_socket):
    try:
        data = client_socket.recv(4096)
        if data:
            json_data = json.loads(data.decode('utf-8'))
            print("Received JSON data:", json_data)

            lon = json_data["lon"]
            lat = json_data["lat"]
            bearing = json_data["bearing"]
            speed = json_data["speed"]

            dataIn = np.array([lon,lat,speed,bearing]).reshape(1, -1)
            print("Data in: ", dataIn)

            y_pred=regressor.predict(dataIn)
            y_pred = y_pred.reshape(-1,1)
            y_pred = scalerY.inverse_transform(y_pred)

            print(y_pred)

            response_data = {"time": y_pred[0][0]}
            response_str = json.dumps(response_data).encode('utf-8')

            client_socket.sendall(response_str)
            print("Sent response:", response_data)
    except Exception as e:
        print("Error:", e)
    finally:
        client_socket.close()

def main():
    server_ip = '127.0.0.1'  
    server_port = 12345    

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((server_ip, server_port))
    server_socket.listen(5)
    print("TCP server is listening on {}:{}".format(server_ip, server_port))

    while True:
        client_socket, client_addr = server_socket.accept()
        print("Accepted connection from:", client_addr)
        handle_client(client_socket)

if __name__ == "__main__":
    main()


