// define what pins each of the traffic lights are connected to.
int red = D1;
int yellow = D4;
int green = D5;

// This is the function that will be called in firmware
// when the build system uses the REST API to call it over the internet
// For example:
//
// curl https://api.spark.io/v1/devices/{DEVICE_ID}/build \
// -d access_token={ACCESS_TOKEN} \
// -d "args=PASSED"

// curl https://api.spark.io/v1/devices/{DEVICE_ID}/build \
// -d access_token={ACCESS_TOKEN} \
// -d "args=BUILDING"

// curl https://api.spark.io/v1/devices/{DEVICE_ID}/build \
// -d access_token={ACCESS_TOKEN} \
// -d "args=FAILED"
int build(String status) {
  if (status == "PASSED"){
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
  } else if (status == "FAILED") {
      digitalWrite(red, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
  } else {
      digitalWrite(yellow, HIGH);
  }
  return 1;
}

// Turn off the lights and set up the Spark.function usage.
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  Spark.function("build", build);
}

// All of our behavior is coming via the Spark.function + API requests,
// so we don't do anything here.
void loop() {}
