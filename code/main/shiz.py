import math
startAngle = 50
turnAngle = 15

def degSin(angle: float):
    return math.sin(math.radians(angle))

def degCos(angle: float):
    return math.cos(math.radians(angle))

def aSinGood(num: float):
    goodNum = max(-1.0, min(1.0, num))
    return math.asin(goodNum)

def generateDistances(angle: float) -> list[float]:
    return [1, 1 / (degSin(180 - startAngle - angle) / degSin(startAngle))]

def getAngle(d1: float, d2: float, angle: float):
    c = getWallLen(d1, d2, angle)
    numer = d1**2 - c**2 - d2**2
    denom = -2 * c * d2
    output = numer / denom
    output = max(-1.0, min(1.0, output))
    return math.degrees(math.acos(output))

def getWallLen(d1: float, d2: float, angle: float):
    return math.sqrt(d2**2 + d1**2 - 2*d2*d1*degCos(angle))


yo = generateDistances(turnAngle)
print(yo)
print(getWallLen(yo[0], yo[1], turnAngle))
print(getAngle(yo[0], yo[1], turnAngle))