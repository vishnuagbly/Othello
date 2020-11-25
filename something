// Author: Ivan Kazmenko (gassa@mail.ru)
module solution;
import std.algorithm;
import std.conv;
import std.range;
import std.stdio;
import std.string;

void main ()
{
	auto tests = readln.strip.to !(int);
	foreach (test; 0..tests)
	{
		auto n = readln.strip.to !(int);
		auto a = readln.splitter.map !(to !(int)).array;
		auto x = a.dup;
		foreach (i; 1..n)
		{
			x[i] = max (x[i], x[i - 1]);
		}
		auto y = a.dup;
		foreach_reverse (i; 0..n - 1)
		{
			y[i] = max (y[i], y[i + 1]);
		}

		auto v = a.maxElement;
		auto maxPlaces = n.iota.filter !(i => a[i] == v).array;
		int lo = maxPlaces[$ / 2];
		int hi = lo + 1;

		while (true)
		{
			if (lo == 0 || hi == n)
			{
				writeln ("NO");
				break;
			}
			if (x[lo - 1] == v && y[hi] == v)
			{
				writeln ("YES");
				writeln (lo, " ", hi - lo, " ", n - hi);
				break;
			}
			int u = (lo - 1 == 0) ? int.min :
			    min (x[lo - 2], a[lo - 1]);
			int w = (hi + 1 >= n) ? int.min :
			    min (y[hi + 1], a[hi]);
			if (u > w)
			{
				v = min (v, a[lo - 1]);
				lo -= 1;
			}
			else
			{
				v = min (v, a[hi]);
				hi += 1;
			}
		}
	}
}
