/* gtkmm example Copyright (C) 2016 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "Application.hpp"

int main(int argc, char* argv[])
{
  // Since this example is running uninstalled, we have to help it find its
  // schema. This is *not* necessary in a properly installed application.
  //Glib::setenv ("GSETTINGS_SCHEMA_DIR", ".", false);

  JSBEdit::Application app;

  // run() will return when the last window has been closed.
  return app.Run(argc, argv);
}
