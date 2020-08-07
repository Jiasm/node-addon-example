#include <napi.h>

Napi::Value GetValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  double* storageData = reinterpret_cast<double*>(info.Data());

  if (storageData == NULL) {
    return Napi::Number::New(env, 0);
  } else {
    return Napi::Number::New(env, *storageData);
  }

}

Napi::Function CurryAdd(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  double* storageData = reinterpret_cast<double*>(info.Data());

  double* result = new double;

  long len, index;
  for (len = info.Length(), index = 0; index < len; index++) {
    double arg = info[index].As<Napi::Number>().DoubleValue();

    *result += arg;
  }

  // 用于多次的计算
  if (storageData != NULL) {
    *result += *storageData;
  }

  Napi::Function fn = Napi::Function::New(env, CurryAdd, "curryAdd", result);

  fn.Set("valueOf", Napi::Function::New(env, GetValue, "valueOf", result));

  return fn;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Napi::Function fn = Napi::Function::New(env, CurryAdd, "curryAdd");

  exports.Set(Napi::String::New(env, "curryAdd"), fn);

  return exports;
}

NODE_API_MODULE(curryadd, Init)