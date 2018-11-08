import json
from flask import Flask, url_for

from grpc import Channel, insecure_channel
from server.protos.entities_pb2 import EntityQueryRequest
from server.protos.entities_pb2_grpc import EntitiesApiStub

from google.protobuf.json_format import MessageToJson


channel = insecure_channel('localhost:50051')
stub = EntitiesApiStub(channel)

app = Flask(__name__)


@app.route('/')
def index():
    entity = MessageToJson(stub.GetEntity(EntityQueryRequest(id='1')))
    return json.dumps(entity, indent=4)


app.run()
