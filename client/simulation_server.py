from concurrent import futures
import grpc
import simulation_pb2
import simulation_pb2_grpc

class SimulationDataServicer(simulation_pb2_grpc.SimulationDataServicer):
    def SendEvent(self, request, context):
        print("Evento recebido:", request.event_data)
        return simulation_pb2.EventResponse(response_message="Evento processado com sucesso!")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    simulation_pb2_grpc.add_SimulationDataServicer_to_server(SimulationDataServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("Servidor rodando na porta 50051")
    server.wait_for_termination()

if __name__ == "__main__":
    serve()
