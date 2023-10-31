{
  description = "dilithium-arm: an ARMv7 Jasmin implementation of Dilithium";

  inputs = {

    flake-utils.url = "github:numtide/flake-utils";

    jasmin-language-server = {
      url = "git+https://github.com/maximedenes/jasmin-language-server?submodules=1";
    };

  };

  outputs = { self, nixpkgs, flake-utils, jasmin-language-server }:
    flake-utils.lib.eachDefaultSystem (system:
  
   let jasmin-lsp = jasmin-language-server.packages.${system}.default; in
   rec {

    packages.default =
      # Notice the reference to nixpkgs here.
      with import nixpkgs { inherit system; };
      
      stdenv.mkDerivation {
        name = "dilithium-arm";
        version = "0.0.1";
        src = ./src;
        buildInputs = [
        ] ++ (with ocamlPackages; [
        ]);
      };

    devShells.default =
      with import nixpkgs { inherit system; };
      mkShell {
        buildInputs = [ jasmin-lsp ];
      };

  });
}
