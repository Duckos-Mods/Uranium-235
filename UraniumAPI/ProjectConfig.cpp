#include "ProjectConfig.hpp"
#include <format>

namespace Uranium
{
	Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
		: major(major), minor(minor), patch(patch)
	{
	}

	CStrWithLength Version::ToString() const
	{
		return CStrWithLength(std::format("{}.{}.{}", major, minor, patch), false);
	}

	bool Version::operator==(const Version& other) const
	{
		return major == other.major && minor == other.minor && patch == other.patch;
	}

	bool Version::operator!=(const Version& other) const
	{
		return !(*this == other);
	}

	bool Version::operator>(const Version& other) const
	{
		if (major > other.major)
		{
			return true;
		}
		else if (major == other.major)
		{
			if (minor > other.minor)
			{
				return true;
			}
			else if (minor == other.minor)
			{
				if (patch > other.patch)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Version::operator<(const Version& other) const
	{
		if (major < other.major)
		{
			return true;
		}
		else if (major == other.major)
		{
			if (minor < other.minor)
			{
				return true;
			}
			else if (minor == other.minor)
			{
				if (patch < other.patch)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Version::operator>=(const Version& other) const
	{
		return !(*this < other);
	}

	bool Version::operator<=(const Version& other) const
	{
		return !(*this > other);
	}
}