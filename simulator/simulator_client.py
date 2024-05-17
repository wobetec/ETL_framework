from multiprocessing import process
import grpc
import rpc.simulation_pb2 as simulation_pb2
import rpc.simulation_pb2_grpc as simulation_pb2_grpc

from data_generator import Simulation

import time
import numpy as np
import multiprocessing

def send_event(event_data):
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = simulation_pb2_grpc.SimulationDataStub(channel)
        response = stub.SendEvent(simulation_pb2.EventRequest(event_data=event_data))
        print("Resposta do servidor:", response.response_message)


def simulator_thread(user_min, user_max):
    start_time = time.perf_counter()
    simulation = Simulation()
    simulation.delete_folders()
    simulation.create_folders()
    print(f"Initialization time: {time.perf_counter() - start_time}")

    # Main loop
    while True:
        start_time = time.perf_counter()
        num_events = np.random.randint(1000, 10000)
        data = simulation.run_cadeanalytics(num_events)
        send_event(data)
        print(f"Execution step time: {time.perf_counter() - start_time}")


if __name__ == "__main__":

    N = 1
    user_min = 500
    user_max = 1000
    delta = int((user_max - user_min) / N)

    processes = []
    for i in range(N):
        p = multiprocessing.Process(target=simulator_thread, args=(user_min + i * delta, user_max + (i+1) * delta))
        processes.append(p)
        p.start()
