/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <WPILib.h>
#include <Drive/DifferentialDrive.h>
#include <Joystick.h>
#include <Drive/MecanumDrive.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Spark.h>
#include <Talon.h>
#include <Timer.h>

using namespace frc;
using namespace std;


/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * The SampleRobot class is the base of a robot application that will
 * automatically call your Autonomous and OperatorControl methods at the right
 * time as controlled by the switches on the driver station or the field
 * controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're
 * inexperienced, don't. Unless you know what you are doing, complex code will
 * be much more difficult under this system. Use IterativeRobot or Command-Based
 * instead if you're new.
 */
class Robot : public SampleRobot {
public:
	Robot() {
		// Note SmartDashboard is not initialized here, wait until
		// RobotInit to make SmartDashboard calls
		m_robotDrive.SetExpiration(0.1);
	}

	void RobotInit() {
		//m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		//m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		//SmartDashboard::PutData("Auto Modes", &m_chooser);

	}

	/*
	 * This autonomous (along with the chooser code above) shows how to
	 * select between different autonomous modes using the dashboard. The
	 * sendable chooser code works with the Java SmartDashboard. If you
	 * prefer the LabVIEW Dashboard, remove all of the chooser code and
	 * uncomment the GetString line to get the auto name from the text box
	 * below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to
	 * the if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as
	 * well.
	 */
	void Autonomous() {
		/* string autoSelected = m_chooser.GetSelected();
		// string autoSelected = SmartDashboard::GetString(
		// "Auto Selector", kAutoNameDefault);
		cout << "Auto selected: " << autoSelected << endl;

		// MotorSafety improves safety when motors are updated in loops
		// but is disabled here because motor updates are not looped in
		// this autonomous mode.
		m_robotDrive.SetSafetyEnabled(false);

		if (autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
			cout << "Running custom Autonomous" << endl;

			// Spin at half speed for two seconds
			m_robotDrive.ArcadeDrive(0.0, 0.5);
			Wait(2.0);

			// Stop robot
			m_robotDrive.ArcadeDrive(0.0, 0.0);
		} else {
			// Default Auto goes here
			cout << "Running default Autonomous" << endl;

			// Drive forwards at half speed for two seconds
			m_robotDrive.ArcadeDrive(-0.5, 0.0);
			Wait(2.0);

			// Stop robot
			m_robotDrive.ArcadeDrive(0.0, 0.0);
		}
		*/
	}

	/*
	 * Runs the motors with mecanum steering.
	 */
	void OperatorControl() override {
		m_robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {
			// Drive with arcade style (use right stick)
			m_robotDrive.DriveCartesian(0.4*stickDrive.GetX(), 0.7*stickDrive.GetY(), 0.8*stickDrive.GetZ(), 0);

			if (stickAux.GetRawButton(1))
			{
				motorShoot.Set(-(stickAux.GetRawAxis(3)));
			} else	{
				motorShoot.Set(0);
			}

			if (stickAux.GetRawButton(11)) {

				motorClimb.Set(1);
			} else if (stickAux.GetRawButton(12))
			{
				motorClimb.Set(-1);
			} else	{
				motorClimb.Set(0);
			}



			motorJumble.Set(stickAux.GetRawButton(2));

			// The motors will be updated every 5ms
			Wait(0.005);
		}
	}

	/*
	 * Runs during test mode
	 */
	void Test() override {}

private:
	// Robot drive system

	Spark motorFR{0};
	Spark motorBR{1};
	Spark motorFL{2};
	Spark motorBL{3};
	Talon motorClimb{6};
	Talon motorJumble{4};
	Talon motorShoot{5};

	MecanumDrive m_robotDrive{motorFL, motorBL, motorFR, motorBR};

	Joystick stickDrive{0};
	Joystick stickAux{1};

	//SendableChooser<string> m_chooser;
	//const string kAutoNameDefault = "Default";
	//const string kAutoNameCustom = "My Auto";
};

START_ROBOT_CLASS(Robot)
