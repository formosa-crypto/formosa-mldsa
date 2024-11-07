let
  pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/6dbbd5a2622d9abf9263a5cb0a85ca218974b085.tar.gz") {};
in pkgs.mkShell {
  packages = [
    (pkgs.python3.withPackages (python-pkgs: with python-pkgs; [
      pycryptodome
    ]))
  ];
  JASMINC = "${pkgs.jasmin-compiler.bin}/bin/jasminc";
  JASMINCT = "${pkgs.jasmin-compiler.bin}/bin/jasminc";
}
