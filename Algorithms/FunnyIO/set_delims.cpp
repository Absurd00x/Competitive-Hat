struct i_love_timus : ctype<char> {
  i_love_timus() : ctype<char>(get_table()) {}
  static mask const* get_table()
  {
    static mask rc[table_size];
    static const char delims[] = " \n.,-:!?";
    for (char delim : delims) {
      rc[(int)delim] = ctype_base::space;
    }
    return &rc[0];
  }
};

cin.imbue(locale(cin.getloc(), new i_love_timus));

