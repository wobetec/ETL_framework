import grpc
import simulation_pb2
import simulation_pb2_grpc

def send_event(event_data):
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = simulation_pb2_grpc.SimulationDataStub(channel)
        response = stub.SendEvent(simulation_pb2.EventRequest(event_data=event_data))
        print("Resposta do servidor:", response.response_message)

if __name__ == "__main__":
    send_event("Dados do evento aqui")
