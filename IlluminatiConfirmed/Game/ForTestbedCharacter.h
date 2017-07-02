#pragma once

//#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include <vector>
#include "Box2D/Box2D.h"
#include <iostream>

enum class KeyEnum {
  RIGHT = GLFW_KEY_D,
  LEFT = GLFW_KEY_A,
  UP = GLFW_KEY_W,
  DOWN = GLFW_KEY_S,
  STOP = GLFW_KEY_SPACE,
  NOTHING = 10000
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

class Character_ {
 public:
  Character_(b2World* world) {

	  {
		  b2BodyDef bd;
		  bd.type = b2_staticBody;
		  bd.position.Set(0.f, 15.f);
		  auto fix = world->CreateBody(&bd);
		  {
			  b2PolygonShape poligon;
			  poligon.SetAsBox(10.f, 0.5f);

			  b2FixtureDef fixture;

			  fixture.shape = &poligon;
			  fixturee = fix->CreateFixture(&fixture);
		  }

		  {
			  b2PolygonShape poligon;
			  poligon.SetAsBox(2.f, 0.5f, {0.f, 3.f}, 0);

			  b2FixtureDef fixture;

			  fixture.shape = &poligon;
			  fixtureee = fix->CreateFixture(&fixture);
		  }

	  }




    {
      b2BodyDef bd;
	  bd.fixedRotation = true;
      bd.type = b2_dynamicBody;
      bd.position.Set(0.f, 10.f);
      bd.linearDamping = 1000.f;
      m_body = world->CreateBody(&bd);

      b2PolygonShape poligon;
      poligon.SetAsBox(1.f, 0.5f);

      b2FixtureDef fixture;
      fixture.friction = 1.f;
      fixture.density = 50.f;
	  fixture.restitution = 0;
	  fixture.isSensor = false;

      fixture.shape = &poligon;
      m_body->SetGravityScale(0.f);

      m_body->CreateFixture(&fixture);
    }
    {
      b2BodyDef bd;
	  bd.position.Set(0.f, 35.f);
      bd.type = b2_dynamicBody;
      bd.position.Set(0.f, 10.f);
      bd.linearDamping = 0.f;
      bd.fixedRotation = true;
      m_body_2 = world->CreateBody(&bd);

      b2PolygonShape poligon;
      poligon.SetAsBox(1.f, 2.f);

      b2FixtureDef fixture;
      fixture.friction = 0.f;
      fixture.density = 0.005f;
	  fixture.isSensor = false;

      fixture.shape = &poligon;

      m_body_2->CreateFixture(&fixture);
    }
    {
      b2PrismaticJointDef jd;
      jd.bodyA = m_body;
      jd.bodyB = m_body_2;
      jd.enableLimit = true;
	  jd.localAnchorA.SetZero();
	  jd.localAnchorB.SetZero();
      jd.localAxisA.Set(0.0f, 1.0f);
      jd.lowerTranslation = 2.5f;
      jd.upperTranslation = 4.0f;
      //jd.enableMotor = true;
      jd.collideConnected = true;
      //jd.maxMotorForce = +10.f;
      //jd.motorSpeed = -100.f;

	  m_joint_prism = static_cast<b2PrismaticJoint*>(world->CreateJoint(&jd));
	  /*
      b2MotorJointDef mjd;
      mjd.Initialize(m_body, m_body_2);
      mjd.maxForce = 2.8f;
      mjd.maxTorque = 0.0f;
	  mjd.linearOffset = { 0, 0 };
	  mjd.collideConnected = true;
	  */
	  b2MotorJointDef mjd;
	  mjd.Initialize(m_body, m_body_2);
	  mjd.maxForce = 1000.0f;
	  mjd.maxTorque = 0.0f;
	  mjd.collideConnected = true;


	  //m_joint->SetLinearOffset({0.f, 1.f});
	  //m_joint->SetAngularOffset(0);
	  m_joint = (b2MotorJoint*)world->CreateJoint(&mjd);

       //m_joint = (b2MotorJoint*)world->CreateJoint(&mjd);
    }
  }

  b2Fixture *fixturee;
  b2Fixture *fixtureee;
  void UpdateForce(KeyEnum key, Settings *settings) {
    switch (key) {
      case KeyEnum::RIGHT: {
		  //m_body_2->SetLinearVelocity({ 0.f, + 40.f });
        m_body->SetLinearVelocity({+300.f, 0.f});
        break;
      }
      case KeyEnum::LEFT: {
		  //m_body_2->SetLinearVelocity({ 0.f, +40.f });
        m_body->SetLinearVelocity({ -300.f, 0.f });
        break;
      }
      case KeyEnum::UP: {
		  //m_body_2->SetLinearVelocity({ 0.f, +40.f });
        m_body->SetLinearVelocity({0.f, +300.f });
        break;
      }
      case KeyEnum::DOWN: {
		  //m_body_2->SetLinearVelocity({ 0.f, +40.f });
		//  for (auto it = m_body->GetContactList(); it; it = it->GetNext())
		//  {
		//	  m_body it->contact->GetFixtureA()
		//}

        m_body->SetLinearVelocity({0.f, -300.f });
        break;
      }
    }
	//if (m_check_collisison)
	//{
	//	m_joint_prism->SetLimits(1.f, 3.f);
	//	m_body_2->SetLinearVelocity({ 0.f, 10.f });
	//}
	

  }

  b2Body* m_body;
  b2Body* m_body_2;
  b2MotorJoint* m_joint;
  b2PrismaticJoint* m_joint_prism;
  bool m_check_collisison = 0;
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
        //        m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(),
        //        true);
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
        //        m_body->ApplyForce(b2Vec2(-force, 0),
        //        m_body->GetWorldCenter(), true);
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
        //        m_body->ApplyForce(b2Vec2(0, force), m_body->GetWorldCenter(),
        //        true);
        b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, -m_max_force));
        b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, m_max_force));
        m_body->ApplyForce(f, p, true);
        break;
      }
      case KeyEnum::DOWN: {
        //        float force = m_body->GetMass() *
        //                      (m_max_speed - m_body->GetLinearVelocity().x) /
        //                      (1 / 60.0);  // f = mv/t
        //        m_body->ApplyForce(b2Vec2(0, -force),
        //        m_body->GetWorldCenter(), true);
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
  Character_ m_ch2 = m_world;

  void Keyboard(int key) override {
    for (auto&& it : keys) {
      if (it.first == static_cast<KeyEnum>(key)) {
        it.second = true;
      }
      if (GLFW_KEY_Q == key) {
		  //m_ch2.m_joint_prism->SetLimits(0.5f, 3.f);
        //m_ch2.m_body_2->SetLinearVelocity({0.f, 10.f});
      }
    }
	m_key = key;
    Test::Keyboard(key);
  }
  int m_key = 0;
  void KeyboardUp(int key) override {
    for (auto&& it : keys) {
      if (it.first == static_cast<KeyEnum>(key)) {
        it.second = false;
      }
    }
    Test::KeyboardUp(key);
  }
  std::vector<std::pair<KeyEnum, bool>> keys = {{KeyEnum::DOWN, false},
                                                {KeyEnum::UP, false},
                                                {KeyEnum::RIGHT, false},
                                                {KeyEnum::LEFT, false}};
  std::string str;

  void Step(Settings* settings) {
	  static auto shadow_pos = m_ch2.m_body->GetPosition();
	  shadow_pos = m_ch2.m_body->GetPosition();
    for (const auto& it : keys) {
      if (it.second == true) {
        m_ch2.UpdateForce(static_cast<KeyEnum>(it.first), settings);
      }
    }

	static int m_time;
	static int dir;

	auto isPress = [this]() {  
		for (auto && it : keys)
		{
			if (it.second == true)
				return true;
		}
		return false; 
	};
	//std::cout << "m_ch2.m_check_collisison: " << m_ch2.m_check_collisison << "isPress(): " << isPress() <<"m_time > 0: "<< (m_time > 0 )<< std::endl;
	if (m_ch2.m_check_collisison && isPress() || m_time > 0 )
	{
		m_time += 1.f * dir;
		if (m_time > 4)
			dir = -1;
		else if (m_time < 1)
			dir = 1;

		//std::cout << "dir: " << dir << "time: " << m_time << std::endl;
		b2Vec2 linearOffset;
		linearOffset.x = 0;
		linearOffset.y = m_time;

		float32 angularOffset = 4.0f * m_time;

		m_ch2.m_joint->SetLinearOffset(linearOffset);
		m_ch2.m_joint->SetAngularOffset(angularOffset);
		g_debugDraw.DrawPoint(linearOffset, 4.0f, b2Color(0.9f, 0.9f, 0.9f));
	}
	


	//std::cout << "Velocity: " << m_ch2.m_body->GetLinearVelocity().x << " : " << m_ch2.m_body->GetLinearVelocity().y<< std::endl;
	//m_ch2.m_body_2->SetLinearVelocity(m_ch2.m_body_2->GetLinearVelocity() + b2Vec2({ 0.f, m_ch2.m_body->GetLinearVelocity().y }));
    Test::Step(settings);
	//m_ch2.m_body_2->SetType(b2_dynamicBody);
	//m_ch2.m_body_2->SetTransform(m_ch2.m_body_2->GetPosition() + (m_ch2.m_body->GetPosition() - shadow_pos), m_ch2.m_body_2->GetAngle());
	shadow_pos = m_ch2.m_body->GetPosition();

    g_debugDraw.DrawString(8, m_textLine + 5, "SPACEEE");
    str += std::string("Mause :") + std::to_string(m_mouseWorld.x) +
           std::string(" : ") + std::to_string(m_mouseWorld.y) +
           std::string("is active: ") + std::to_string(m_ch.m_body->IsActive());
	str += std::string(" fixture position: ") + std::to_string(static_cast<const b2PolygonShape*>(m_ch2.fixturee->GetShape())->m_centroid.x) + std::string(" : ") + std::to_string(static_cast<const b2PolygonShape*>(m_ch2.fixturee->GetShape())->m_centroid.y);
	str += std::string(" fixture position: ") + std::to_string(static_cast<const b2PolygonShape*>(m_ch2.fixtureee->GetShape())->m_centroid.x) + std::string(" : ") + std::to_string(static_cast<const b2PolygonShape*>(m_ch2.fixtureee->GetShape())->m_centroid.y);
	g_debugDraw.DrawString(5, m_textLine, str.c_str());
    g_debugDraw.DrawPoint(m_mouseWorld, 5, b2Color(100, 100, 100));
    str = "";
  }

  void BeginContact(b2Contact* contact) override
  {
	  m_ch2.m_check_collisison = true;
	  /*for (auto && it : keys)
	  {
		  if (it.second == true)
		  {
			  m_ch2.m_joint_prism->SetLimits(1.f, 3.f);
			  m_ch2.m_body_2->SetLinearVelocity({ 0.f, 10.f });
			  return;
		  }
	  }*/

	  //m_ch2.m_joint_prism->SetLimits(1.f, 4.f);
	  static int k;
	  //m_ch2.m_body_2->SetTransform(m_ch2.m_body_2->GetPosition() + b2Vec2({0.f, 0.2f}), m_ch2.m_body_2->GetAngle());
	  std::cout << "BeginContact: " << k++ << std::endl;
  }
  void EndContact(b2Contact* contact) override
  {
	  m_ch2.m_check_collisison = false;
	  static int k;
	  std::cout << "EndContact: " << k++ << std::endl;
  }
  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
  {
	  static int k;
	  //std::cout << "PreSolve: " << k++ << std::endl;
  }
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
  {
	  static int k;
	  //std::cout << "PostSolve: " << k++ << std::endl;
  }
  
  static Test* Create() { return new MyTesttt; }
};
