import Foundation

public func bench<T>(vectorSize size:UInt, createT:(UInt)->T, hashT:(T)->UInt) -> UInt
{
	var vec:[T] = []
	for i in 0..<size {
		vec.append(createT(i))
	}

	let checksum = vec.reduce(0) {$0&+hashT($1)}
	while !vec.isEmpty {
		vec.popLast()
	}
	return checksum
}

public struct PQnode
{
	public let key : Double
	public let item : UInt
}

let n:UInt = 100_000_000
print("Samples: \(n)")
let start = Date()

print("Bench1:", bench(vectorSize:n, createT:{UInt8($0%256)}, hashT:{UInt($0)}))
print("Bench2:", bench(vectorSize:n, createT:{UInt32($0)}, hashT:{UInt($0)}))
print("Bench3:", bench(vectorSize:n, createT:{PQnode(key:Double($0), item:UInt($0))}, hashT:{UInt($0.key)&+$0.item}))

let time = -start.timeIntervalSinceNow
print("Time: \(time) s\n")
