#include "Metrics.hpp"


namespace JSBEdit
{
	Metrics::WingArea::WingArea(double wingArea, Glib::ustring unit) : m_Unit{unit}
	{
		// check if WingArea is negative
		if (wingArea > 0)
		{
			m_WingArea = wingArea;
		}
	}

	Metrics::WingSpan::WingSpan(double wingSpan, Glib::ustring unit)
	{
		// check if WingArea is negative
		if (wingSpan > 0)
		{
			m_WingSpan = wingSpan;
		}
	}

	Metrics::WingIncidence::WingIncidence(double wingIncidence, Glib::ustring unit) : m_WingIncidence{ wingIncidence }, m_Unit{unit}
	{
	}

	Metrics::Chord::Chord(double chordLength, Glib::ustring unit) : m_chord{ chordLength }, m_Unit{ unit }
	{
	}

	Metrics::HTailArea::HTailArea(double horizTailArea, Glib::ustring unit) : m_hTailArea{ horizTailArea }, m_Unit{unit}
	{
	}

	Metrics::HTailArm::HTailArm(double horizTailArm, Glib::ustring unit): m_hTailArm{horizTailArm}, m_Unit{unit}
	{
	}

	Metrics::VTailArea::VTailArea(double vertTailArea, Glib::ustring unit) : m_vTailArea{ vertTailArea }, m_Unit{unit}
	{
	}

	Metrics::VTailArm::VTailArm(double vertTailArm, Glib::ustring unit) : m_vTailArm{ vertTailArm }, m_Unit{unit}
	{
	}

	Metrics::Location::Location(double x, double y, double z, Glib::ustring name, Glib::ustring unit) : m_name{ name }, m_Unit{ unit }, m_X{x}, m_Y{y}, m_Z{z}
	{
	}

};