#include <napi.h>

void bubbleSort(double* arr, int len) {
  double temp;
  int i, j;
  for (i = 0; i < len; i++) {
    for (j = i + 1; j < len; j++) {
      if (*(arr + i) < *(arr + j)) {
        temp = *(arr + i);
        *(arr + i) = *(arr + j);
        *(arr + j) = temp;
      }
    }
  }
}

Napi::Value Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Array array = info[0].As<Napi::Array>();


  int len = array.Length(), i;

  // 返回值
  Napi::Array arr = Napi::Array::New(env, len);

  double* list = new double[len];

  // 将 Array 转换为 c++ 可方便使用的 double 数组
  for (i = 0; i < len; i++) {
    Napi::Value i_v = array[i];

    list[i] = i_v.ToNumber().DoubleValue();
  }

  // 执行排序
  bubbleSort(list, len);

  // 将 double 数组转换为要传递给 JS 的数据类型
  for (i = 0; i < len; i++) {
    arr[i] = Napi::Number::New(env, list[i]);
  }

  return arr;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "bubble"), Napi::Function::New(env, Add));
  return exports;
}

NODE_API_MODULE(bubble, Init)
