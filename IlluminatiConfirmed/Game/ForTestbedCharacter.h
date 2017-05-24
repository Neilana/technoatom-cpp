#pragma once

//#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Box2D/Box2D.h"

enum class KeyEnum {
  RIGHT = GLFW_KEY_D,
  LEFT = GLFW_KEY_A,
  UP = GLFW_KEY_W,
  DOWN = GLFW_KEY_S,
  STOP = GLFW_KEY_SPACE
};

class PID {
 public:
  // Kp -  proportional gain
  // Ki -  Integral gain
  // Kd -  derivative gain
  // dt -  loop interval time
  // max - maximum value of manipulated variable
  // min - minimum value of manipulated variable
  PID(double dt, double max, double min, double Kp, double Kd, double Ki,
      double integral)
      : m_dt(dt),
        m_max(max),
        m_min(min),
        m_Kp(Kp),
        m_Kd(Kd),
        m_Ki(Ki),
        m_integral(integral) {}

  // Returns the manipulated variable given a setpoint and current process value
  double calculate(double setpoint, double pv) {
    // Calculate error
    double error = setpoint - pv;

    // Proportional term
    double Pout = m_Kp * error;

    // Integral term
    m_integral += error * m_dt;
    double Iout = m_Ki * m_integral;

    // Derivative term
    double derivative = (error - _pre_error) / m_dt;
    double Dout = m_Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Restrict to max/min
    if (output > m_max)
      output = m_max;
    else if (output < m_min)
      output = m_min;

    // Save error to previous error
    _pre_error = error;

    return output;
  }

 private:
  double m_dt;
  double m_max;
  double m_min;
  double m_Kp;
  double m_Kd;
  double m_Ki;
  double _pre_error;
  double m_integral;
};

class Character {
 public:
  Character(b2World* world /*, b2Body *ground*/) {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    // body_def.fixedRotation = true;

    body_def.position.Set(0, 5.0f);
    m_body = world->CreateBody(&body_def);

    b2CircleShape circle_shape;
    circle_shape.m_radius = 1.f;
    b2FixtureDef fixture;
    fixture.shape = &circle_shape;
    fixture.density = 1.0f;
    fixture.friction = 0.3f;

    m_body->CreateFixture(&fixture);
    m_body->SetLinearDamping(1.f);
    m_body->SetAngularDamping(1.f);
  }

  void UpdateForce(KeyEnum key) {
    switch (key) {
      case KeyEnum::RIGHT: {
//        float force = m_body->GetMass() *
//                      (m_max_speed - m_body->GetLinearVelocity().x) /
//                      (1 / 60.0);  // f = mv/t
//        m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
         b2Vec2 f = m_body->GetWorldVector(b2Vec2(m_max_force, 0.f));
         b2Vec2 p = m_body->GetWorldPoint(b2Vec2(m_max_force, 0.f));
         m_body->ApplyForce(f, p, true);
        // m_body->ApplyForce(f, p, true);
        // m_body->ApplyTorque(-50.f, true);
        break;
      }
      case KeyEnum::LEFT: {
//        float force = m_body->GetMass() *
//                      (m_max_speed - m_body->GetLinearVelocity().x) /
//                      (1 / 60.0);  // f = mv/t
//        m_body->ApplyForce(b2Vec2(-force, 0), m_body->GetWorldCenter(), true);
         b2Vec2 f = m_body->GetWorldVector(b2Vec2(-m_max_force, 0.f));
         b2Vec2 p = m_body->GetWorldPoint(b2Vec2(m_max_force, 0.f));
         m_body->ApplyForce(f, p, true);
        // m_body->ApplyTorque(+50.f, true);
        break;
      }
      case KeyEnum::UP: {
//        float force = m_body->GetMass() *
//                      (m_max_speed - m_body->GetLinearVelocity().x) /
//                      (1 / 60.0);  // f = mv/t
//        m_body->ApplyForce(b2Vec2(0, force), m_body->GetWorldCenter(), true);
         b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, -m_max_force));
         b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, m_max_force));
         m_body->ApplyForce(f, p, true);
        break;
      }
      case KeyEnum::DOWN: {
//        float force = m_body->GetMass() *
//                      (m_max_speed - m_body->GetLinearVelocity().x) /
//                      (1 / 60.0);  // f = mv/t
//        m_body->ApplyForce(b2Vec2(0, -force), m_body->GetWorldCenter(), true);
         b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, m_max_force));
         b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, m_max_force));
         m_body->ApplyForce(f, p, true);
        break;
      }
    }
  }

  ~Character() { m_body->GetWorld()->DestroyBody(m_body); }
  b2Body* m_body;

 private:
  float m_max_speed = 2.f;
  float m_max_force = 200.f;
};

class MyTesttt : public Test {
 public:
  MyTesttt() {
    m_world->SetGravity(b2Vec2(0.0f, 0.0f));

    const float32 k_restitution = 0.4f;

    b2Body* ground;
    {
      b2BodyDef bd;
      bd.position.Set(0.0f, 20.0f);
      ground = m_world->CreateBody(&bd);

      b2EdgeShape shape;

      b2FixtureDef sd;
      sd.shape = &shape;
      sd.density = 0.0f;
      sd.restitution = k_restitution;

      // Left vertical
      shape.Set(b2Vec2(-20.0f, -20.0f), b2Vec2(-20.0f, 20.0f));
      ground->CreateFixture(&sd);

      // Right vertical
      shape.Set(b2Vec2(20.0f, -20.0f), b2Vec2(20.0f, 20.0f));
      ground->CreateFixture(&sd);

      // Top horizontal
      shape.Set(b2Vec2(-20.0f, 20.0f), b2Vec2(20.0f, 20.0f));
      ground->CreateFixture(&sd);

      // Bottom horizontal
      shape.Set(b2Vec2(-20.0f, -20.0f), b2Vec2(20.0f, -20.0f));
      ground->CreateFixture(&sd);
    }
  }

  Character m_ch = m_world;

  void Keyboard(int key) {
    m_ch.UpdateForce(static_cast<KeyEnum>(key));
    Test::Keyboard(key);
  }

  std::string str;

  void Step(Settings* settings) {
    Test::Step(settings);
    str = std::string("Mause :") + std::to_string(m_mouseWorld.x) +
          std::string(" : ") + std::to_string(m_mouseWorld.y) +
          std::string("is active: ") + std::to_string(m_ch.m_body->IsActive());
    g_debugDraw.DrawString(5, m_textLine, str.c_str());
    g_debugDraw.DrawPoint(m_mouseWorld, 5, b2Color(100, 100, 100));
  }

  static Test* Create() { return new MyTesttt; }
};
