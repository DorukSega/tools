{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  pname = "doruk-tools";
  version = "1.0";

  src = ./.;

  buildInputs = [ pkgs.libgcc ];

  buildPhase = ''
    mkdir -p bin
    for src in *.c; do
      prog_name=$(basename $src .c)
      gcc -Wall -Wextra -pedantic -O2 $src -o ./bin/$prog_name
    done
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp -r bin/* $out/bin/
  '';

  meta = with pkgs.lib; {
    description = "tools";
    license = licenses.mit;
    maintainers = with maintainers; [ "doruk" ];
  };
}
