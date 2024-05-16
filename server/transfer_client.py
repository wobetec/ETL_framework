import grpc
import transfer_pb2
import transfer_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = transfer_pb2_grpc.FileServiceStub(channel)
        with open('f.txt', 'rb') as f:
            file_content = f.read()
        response = stub.UploadFile(transfer_pb2.FileUploadRequest(filename='tony.txt', file_content=file_content))
        print("Client received: " + response.message)

if __name__ == '__main__':
    run()