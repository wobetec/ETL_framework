from concurrent import futures
import grpc
import rpc.simulation_pb2 as simulation_pb2
import rpc.simulation_pb2_grpc as simulation_pb2_grpc

import socket


class SimulationDataServicer(simulation_pb2_grpc.SimulationDataServicer):
    def SendEvent(self, request, context):
        data = request.event_data
        print("Recebido do cliente: OK")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect(('localhost', 8080))
        sock.sendall(data.encode('utf-8'))
        sock.close()
        return simulation_pb2.EventResponse(response_message="OK")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    simulation_pb2_grpc.add_SimulationDataServicer_to_server(SimulationDataServicer(), server)
    server.add_insecure_port("0.0.0.0:50051")
    server.start()
    print("Servidor rodando na porta 50051")
    server.wait_for_termination()

if __name__ == "__main__":
    serve()
