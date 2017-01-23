typedef void Cptprof;

#ifdef __cplusplus
extern "C" {
#endif
  Cptprof *getInstance();
  void initialize(const Cptprof *t, char *name);
  void start(const Cptprof *t, char *name);
  void stop(const Cptprof *t);
  void finalize(const Cptprof *t);
  void print(const Cptprof *t);
  void cancel(const Cptprof *t);
#ifdef __cplusplus
}
#endif