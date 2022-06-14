from fastapi import FastAPI
import redis
app = FastAPI()

r = redis.Redis(
	host='localhost',
	port=6379,
)

@app.get("/")
async def root():
    return {"message": "Promexpo"}

@app.get("/vden/{value}")
async def set_temp(value):
    r.set("vden", value)
    return "vden value("+str(value)+") published"

@app.get("/tlimit/{value}")
async def set_battery(value):
    r.set("tlimit", value)
    return "tlimit value("+str(value)+") published"

@app.get("/eservice/{value}")
async def set_ldr(value):
    r.set("eservice", value)
    return "eservice value("+str(value)+") published"

 