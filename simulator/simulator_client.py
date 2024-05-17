import grpc
import rpc.simulation_pb2 as simulation_pb2
import rpc.simulation_pb2_grpc as simulation_pb2_grpc

from data_generator import Simulation

import time
import numpy as np

def send_event(event_data):
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = simulation_pb2_grpc.SimulationDataStub(channel)
        response = stub.SendEvent(simulation_pb2.EventRequest(event_data=event_data))
        print("Resposta do servidor:", response.response_message)


if __name__ == "__main__":
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

