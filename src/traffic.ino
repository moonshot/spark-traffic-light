// define what pins each of the traffic lights are connected to.
int red = D1;
int yellow = D4;
int green = D5;

char build_color[16] = "NONE";
char notify_color[16] = "NONE";

// This is the function that will be called in firmware
// when the build system uses the REST API to call it over the internet
// For example:
//
// curl https://api.spark.io/v1/devices/{DEVICE_ID}/build \
// -d access_token={ACCESS_TOKEN} \
// -d "args=green"
int build(String color) {
  color.toCharArray(build_color, 16);
  if (color == "green"){
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
  } else if (color == "red") {
      digitalWrite(red, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
  } else if (color == "off") {
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
  } else {
      digitalWrite(yellow, HIGH);
  }
  return 1;
}

int notify(String ballcolor) {
  // For ballcolor's values, see the jenkins docs at:
  // http://javadoc.jenkins-ci.org/hudson/model/BallColor.html
  ballcolor.toCharArray(notify_color, 16);
  if (ballcolor == "Success"){
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
  } else if (ballcolor == "Failed") {
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
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  Spark.function("build", build);
  Spark.function("notify", notify);

  Spark.variable("build_color", &build_color, STRING);
  Spark.variable("notify_color", &notify_color, STRING);
}

// All of our behavior is coming via the Spark.function + API requests,
// so we don't do anything here.
void loop() {}
