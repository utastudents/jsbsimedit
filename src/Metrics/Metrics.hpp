#pragma once

#include <glibmm.h>
#include <vector>

namespace JSBEdit
{
	// Metrics is layout out in a specific order that conforms to the 
	// JSBSim.xsd schema
	class Metrics
	{
		// Nested classes for grouping of the data. It basically looks pretty - Ellis

		/*
		  Wing area (reference area) for the vehicle being modeled. The default unit
		  is square feet (FT2)
		*/
		class WingArea 
		{
			// can not be negative, per the XSD
			double m_WingArea = 0;
			Glib::ustring m_Unit;
		public:
			WingArea() = default;
			WingArea(double WingArea, Glib::ustring unit = "FT2");
			double& GetWingArea() { return m_WingArea; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  Wingspan (lateral reference length) for the vehicle being modeled. The
          default unit is feet (FT).
		*/
		class WingSpan 
		{
			// can not be negative, per the XSD
			double m_WingSpan = 0;
			Glib::ustring m_Unit;
		public:
			WingSpan() = default;
			WingSpan(double WingSpan, Glib::ustring unit = "FT");
			double& GetWingSpan() { return m_WingSpan; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  The angle the wing makes with the fuselage centerline  for the vehicle being modeled. The default unit
		  is degrees (DEG).
		*/
		class WingIncidence 
		{
			double m_WingIncidence = 0;
			Glib::ustring m_Unit;
		public:
			WingIncidence() = default;
			WingIncidence(double wingIncidence, Glib::ustring unit = "DEG");
			double& GetWindIncidence() { return m_WingIncidence; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  Chord (longitudinal reference length) for the vehicle being modeled. The default
          unit is feet (FT).
		*/
		class Chord 
		{
			double m_chord = 0;
			Glib::ustring m_Unit;
		public:
			Chord() = default;
			Chord(double chordLength, Glib::ustring unit = "FT");
			double& GetChordLength() { return m_chord; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  Horizontal tail area. The default unit is square feet (FT2).
		*/
		class HTailArea 
		{
			double m_hTailArea = 0;
			Glib::ustring m_Unit;
		public:
			HTailArea() = default;
			HTailArea(double horizTailArea, Glib::ustring unit = "FT2");
			double& GetHTailArea() { return m_hTailArea; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  Horizontal tail arm. This is the distance from the center of gravity
          to the quarter chord of the horizontal tail. The default unit is feet (FT).
		*/
		class HTailArm 
		{
			double m_hTailArm = 0;
			Glib::ustring m_Unit;
		public:
			HTailArm() = default;
			HTailArm(double horizTailArm, Glib::ustring unit = "FT");
			double& GetHTailArm() { return m_hTailArm; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  Vertical tail area. The default unit is square feet (FT2).
		*/
		class VTailArea 
		{
			double m_vTailArea = 0;
			Glib::ustring m_Unit;
		public:
			VTailArea() = default;
			VTailArea(double vertTailArea, Glib::ustring unit = "FT");
			double& GetVTailArea() { return m_vTailArea; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		/*
		  Vertical tail arm. The default unit is feet (FT).
		*/
		class VTailArm 
		{
			double m_vTailArm = 0;
			Glib::ustring m_Unit;
		public:
			VTailArm() = default;
			VTailArm(double vertTailArm, Glib::ustring unit = "FT");
			double& GetVTailArm() { return m_vTailArm; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }
		};

		class Location
		{
			Glib::ustring m_name;
			Glib::ustring m_Unit;
		public:
			Location() = default;
			Location(double x, double y, double z, Glib::ustring name, Glib::ustring unit = "IN");
			double& X() { return m_X; }
			double& Y() { return m_Y; }
			double& Z() { return m_Z; }
			Glib::ustring& GetName() { return m_name; }
			Glib::ustring& GetUnit() { return m_Unit; }
			void SetUnit(Glib::ustring string) { m_Unit = string; }

			double m_X = 0;
			double m_Y = 0;
			double m_Z = 0;
		};

	public:
		Metrics() {}

		WingArea wingarea;
		WingSpan wingspan;
		WingIncidence wingincidence;
		Chord chord;
		HTailArea htailarea;
		HTailArm htailarm;
		VTailArea vtailarea;
		VTailArm vtailarm;
		std::vector<Location> locations;
	};
};