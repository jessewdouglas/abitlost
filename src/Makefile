# Copyright (C) 2022 Jesse Douglas.

# This file is part of A Bit Lost.

# A Bit Lost is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with
# this program. If not, see <https://www.gnu.org/licenses/>.

P=abitlost
OBJECTS=abitlost.o
CFLAGS=-std=c99 -Wall -Wextra -pedantic -O2

$(P): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(P) $(OBJECTS)
