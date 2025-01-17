let
  pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/3ca2cedac25e364aaa53599c85f16e89c3305c1d.tar.gz") {};
in pkgs.mkShell {
  packages = [
    (pkgs.python3.withPackages (python-pkgs: with python-pkgs; [
      pycryptodome
      pytest
      gitpython
    ]))
  ];
  JASMINC = "${pkgs.jasmin-compiler.bin}/bin/jasminc";
  JASMINCT = "${pkgs.jasmin-compiler.bin}/bin/jasmin-ct";
}
