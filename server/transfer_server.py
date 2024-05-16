import grpc
from concurrent import futures
import time
import transfer_pb2
import transfer_pb2_grpc

class FileServiceServicer(transfer_pb2_grpc.FileServiceServicer):
    def UploadFile(self, request, context):
        with open(request.filename, 'wb') as f:
            f.write(request.file_content)
        return transfer_pb2.FileUploadResponse(message="File received successfully")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    transfer_pb2_grpc.add_FileServiceServicer_to_server(FileServiceServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started, listening on port 50051")
    try:
        while True:
            time.sleep(86400)
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    serve()