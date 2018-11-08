from grpc import Channel, insecure_channel
from greeter.protos.greet_pb2 import GreetReply, GreetRequest
from greeter.protos.greet_pb2_grpc import GreeterStub

channel = insecure_channel('localhost:50051')
stub = GreeterStub(channel)

request = GreetRequest(name='Bolous')

print stub.SayHelloVoid(request).message
print stub.SayHello(request).message