import json
from flask import Flask, url_for, jsonify, request

from grpc import Channel, insecure_channel
from server.protos.entities_pb2 import EntityQueryRequest
from server.protos.entities_pb2_grpc import EntitiesApiStub
from google.protobuf.json_format import MessageToJson


channel = insecure_channel('localhost:50050')
stub = EntitiesApiStub(channel)

app = Flask(__name__)


@app.route('/')
def index():
    try:
        entity = stub.GetEntity(EntityQueryRequest(id=request.args.get('id')))
        return MessageToJson(entity)
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': 'error'})

app.run()
