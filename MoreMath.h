#pragma once
class MoreMath
{
	public:
		/// <summary>
		/// Returns the sign of a number (-1, 1 or 0)
		/// </summary>
		/// <param name="value">Number to get the sign of</param>
		/// <returns>Sign of a number (-1, 1 or 0)</returns>
		static int sign(double value);
		/// <summary>
		/// Clamps the value
		/// </summary>
		/// <param name="value">Value to be clamped</param>
		/// <param name="min">Min</param>
		/// <param name="max">Max</param>
		/// <returns>Clamped value</returns>
		static double clamp(double value, double min, double max);
};

