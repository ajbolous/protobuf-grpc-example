from grpc import Channel, insecure_channel
from server.protos.entities_pb2 import EntityQueryRequest
from server.protos.entities_pb2_grpc import EntitiesApiStub

channel = insecure_channel('localhost:50051')
stub = EntitiesApiStub(channel)

request = EntityQueryRequest(id='1')
print stub.GetEntity(request)
