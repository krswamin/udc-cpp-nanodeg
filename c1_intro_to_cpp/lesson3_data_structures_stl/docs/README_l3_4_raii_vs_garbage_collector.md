## 1. Garbage collector
Question: Does c++ have a garbage collector ?\
Answer: 
- Standard C++ has no garbage collector.
- Instead, it uses Deterministic destruction:RAII (Resource Acquisition Is Initialization). 
- That means objects are cleaned up at a known time (when they go out of scope), not “eventually.”
- C++ has no garbage collector because it doesn’t need one — RAII gives you stronger, deterministic guarantees.

## 2. RAII based Memory Management
The killer insight most people miss
- RAII ≠ manual memory management
- Modern C++ almost never uses new/delete.
- This is automatic memory management — just deterministic.
- RAII is also not just about memory management. It takes care of locks, files, sockets, exception safety as well.
```
std::vector<int> v;
std::unique_ptr<Foo> f;
```

### 2.1. Stack allocation (most common)

```
void f() {
    int x = 10;          // destroyed at end of scope
}                         // 💥 gone immediately
```

### 2.2. RAII-managed heap objects
```
{
    std::unique_ptr<int> p = std::make_unique<int>(42);
} // memory freed right here
```
### 2.3. Containers manage memory for you
```
std::vector<int> v = {1, 2, 3};
// v releases its memory in its destructor
```

## 3.1 RAII vs GC comparison
| Aspect                        | RAII (C++)                   | Garbage Collector (Java, Go, JS)    |
| ----------------------------- | ---------------------------- | ----------------------------------- |
| Memory freed                  | At scope end (deterministic) | When GC runs (non-deterministic)    |
| Handles files, locks, sockets | ✅ naturally                  | ⚠️ must use `try/finally` / `defer` |
| Exception safety              | ✅ built-in                   | ⚠️ manual patterns                  |
| Runtime pauses                | ❌ none                       | ⚠️ possible GC pauses               |
| Programmer effort             | ⚠️ higher                    | ✅ lower                             |
| Performance predictability    | ✅ high                       | ⚠️ varies                           |
| Cycles handled                | ❌ (unless weak refs)         | ✅                                   |
| Simplicity for large apps     | ⚠️ harder                    | ✅ easier                            |


### 3.2 Languages with a garbage collector (by default)
Mainstream, widely used
- Java — JVM GC (G1, ZGC, Shenandoah, etc.)
- C# / .NET — Generational GC
- Go — Concurrent, low-latency GC
- JavaScript — GC in all major engines (V8, SpiderMonkey)
- Python — Reference counting + cyclic GC
- Ruby — Generational, incremental GC
- PHP — Reference counting + GC
- Dart — Generational GC
- Kotlin (JVM) — Uses JVM GC
- Scala (JVM) — Uses JVM GC

| Language  | Memory cleanup                        |
| --------- | ------------------------------------- |
| Java / C# | Garbage collector (non-deterministic) |
| Python    | Ref counting + GC                     |
| **C++**   | RAII + deterministic destruction      |


### 3.3 When RAII is clearly better
- RAII wins when timing matters.
- Operating systems
- Game engines
- Real-time / low-latency systems
- Embedded software
- Code managing scarce OS or hardware resources

### 3.4 When GC is clearly better
- GC wins when scale and complexity matter more than exact timing.
- Large backend services
- Web servers
- Data pipelines
- Product-heavy applications with huge object graphs





