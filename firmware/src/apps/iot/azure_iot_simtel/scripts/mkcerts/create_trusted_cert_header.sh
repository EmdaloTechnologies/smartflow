#!/bin/bash
# Copyright (c) Microsoft Corporation. All rights reserved.
# SPDX-License-Identifier: MIT

set -o errexit # Exit if command failed
set -o nounset # Exit if variable not set
set -o pipefail # Exit if pipe failed

# Get certs
echo "Getting DigiCert Global Root G2 and Baltimore Cyber Trust Root certs from cacerts.digicert.com"
wget -q https://cacerts.digicert.com/DigiCertGlobalRootG2.crt.pem -O digicert.pem
wget -q https://cacerts.digicert.com/BaltimoreCyberTrustRoot.crt.pem -O baltimore.pem

# Baltimore Cert has a blank line at the end; remove it
sed -i '$ d' baltimore.pem

# Create a root_ca_cert file from the two certs
echo "Creating root_ca_cert.pem"
cat digicert.pem > root_ca_cert.pem
cat baltimore.pem >> root_ca_cert.pem

# Create a root_ca_cert.pem.h file from the two certs
echo "Creating root_ca_cert.pem.h"
sed -e 's/$/\\n"/' digicert.pem > tmp1
sed -e 's/^/"/' tmp1 > tmp2

sed -e 's/$/\\n"/' baltimore.pem > tmp3
sed -e 's/^/"/' tmp3 > tmp4
sed -e '$s/$/;/' tmp4 > tmp5

echo "unsigned const char root_ca_cert_pem[] =" > root_ca_cert.pem.h
echo "/* Digi Cert Global Root G2 */" >> root_ca_cert.pem.h
cat tmp2 >> root_ca_cert.pem.h
echo "/* Baltimore Cyber Trust Root */" >> root_ca_cert.pem.h
cat tmp5 >> root_ca_cert.pem.h

if [ $# -eq 1 ]
then
	cp root_ca_cert.pem.h $1
fi

# Tidy up
echo "Removing temp files"
rm tmp1 tmp2 tmp3 tmp4 tmp5
rm baltimore.pem
rm digicert.pem
