import subprocess
import os
from flask import Flask, request, jsonify, send_from_directory
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.join(BASE_DIR, "sim.exe")

def run(args):
    result = subprocess.run(
        [EXE] + args,
        capture_output=True,
        text=True,
        cwd=BASE_DIR
    )
    stdout = result.stdout.strip()
    stderr = result.stderr.strip()
    print(f"CMD: {args}")
    print(f"STDOUT: {repr(stdout)}")
    if stderr:
        print(f"STDERR: {repr(stderr)}")
    return stdout

def success(out):
    return "ok" in out.lower()

# Serve the GUI
@app.route("/")
def index():
    return send_from_directory(BASE_DIR, "gui.html")

@app.route("/init", methods=["POST"])
def init():
    out = run(["init"])
    return jsonify({"success": success(out)})

@app.route("/addnode", methods=["POST"])
def addnode():
    data = request.json
    if not data or "node" not in data:
        return jsonify({"success": False, "message": "Missing node field"})
    out = run(["addnode", data["node"]])
    return jsonify({"success": success(out)})

@app.route("/addedge", methods=["POST"])
def addedge():
    data = request.json
    if not data or "a" not in data or "b" not in data or "w" not in data:
        return jsonify({"success": False, "message": "Missing fields"})
    out = run(["addedge", data["a"], data["b"], str(data["w"])])
    return jsonify({"success": success(out)})

@app.route("/dijkstra", methods=["POST"])
def dijkstra():
    data = request.json
    if not data or "src" not in data or "dst" not in data:
        return jsonify({"success": False, "message": "Missing src or dst"})
    out = run(["dijkstra", data["src"], data["dst"]])
    for line in out.splitlines():
        line = line.strip()
        if " " in line and "," in line.split(" ")[0]:
            parts = line.split(" ")
            path = parts[0].split(",")
            cost = int(parts[1])
            return jsonify({"success": True, "path": path, "cost": cost})
    if "nopath" in out:
        return jsonify({"success": False, "message": "No path found"})
    return jsonify({"success": False, "message": "Unexpected output: " + out})

@app.route("/mst", methods=["POST"])
def mst():
    out = run(["mst"])
    lines = [l.strip() for l in out.splitlines() if l.strip()]
    
    cost = None
    edge_line = None
    for line in lines:
        # find the cost line (pure number)
        if line.isdigit() and cost is None:
            cost = int(line)
        # find the edge line (contains spaces and commas like "A B,B C,")
        elif "," in line and " " in line and cost is not None:
            edge_line = line

    if cost is None:
        return jsonify({"success": False, "message": "Unexpected output: " + out})

    if edge_line is None:
        # edges not printed yet — main_function.cpp not updated/recompiled
        return jsonify({"success": True, "cost": cost, "edges": []})

    mst_edges = []
    for e in edge_line.split(","):
        e = e.strip()
        if e:
            parts = e.split(" ")
            if len(parts) == 2:
                mst_edges.append({"a": parts[0], "b": parts[1]})

    return jsonify({"success": True, "cost": cost, "edges": mst_edges})
@app.route("/getnodes", methods=["GET"])
def getnodes():
    out = run(["getnodes"])
    for line in out.splitlines():
        line = line.strip()
        if line and "graph" not in line.lower() and "loaded" not in line.lower():
            nodes = [n.strip() for n in line.split(",") if n.strip()]
            return jsonify({"nodes": nodes})
    return jsonify({"nodes": []})

@app.route("/getedges", methods=["GET"])
def getedges():
    out = run(["getedges"])
    edges = []
    for line in out.splitlines():
        line = line.strip()
        if line:
            for e in line.split(","):
                e = e.strip()
                if e:
                    parts = e.split(" ")
                    if len(parts) == 3:
                        edges.append({"a": parts[0], "b": parts[1], "w": int(parts[2])})
    return jsonify({"edges": edges})

if __name__ == "__main__":
    print(f"EXE path: {EXE}")
    print(f"EXE exists: {os.path.exists(EXE)}")
    print("Server running on http://localhost:8080")
    print("Open http://localhost:8080 in your browser to use the GUI.")
    app.run(port=8080, debug=False)