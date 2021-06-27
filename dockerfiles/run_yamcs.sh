#!/bin/bash

# only supports one file currently. Should add support for multiple files in the future
YAMCS_WEST_FILE='/yamcs/templates/template.west.yaml'
COPY_LOCATION='/yamcs/src/main/yamcs/etc/yamcs.west.yaml'

WARNING_MESSAGE=' \
######################### WARNING ########################## \
# DO NOT MODIFY THIS FILE AS IT IS AUTO GENERATED          # \
# INSTEAD MODIFY THE SAME NAMED FILE (PREFIXED WITH        # \
# template) IN THE TEMPLATES folder                  # \
######################### WARNING ########################## \
'

# copy file to target location
cp $YAMCS_WEST_FILE $COPY_LOCATION

# copy warning message
sed -i "1s/^/$WARNING_MESSAGE\n\n/" $COPY_LOCATION

# loop through every environment variable (.env file variables will be here)
# and replace with the required value
output='Inserted env =>'



while IFS='=' read -r -d '' n v; do
    # sed can't handle any '/' so just ignore any that have one
    if [[ $v != *"/"* ]]; then

        # check to see if the key exists (so we can add it to the output string)
        grep -q $n $COPY_LOCATION
        if [ $? -eq 0 ]
        then
            # perform the replacement
            sed -i "s/\$$n/$v/g" $COPY_LOCATION

            # add to the output string
            output="$output $n: $v, "
        fi
    fi
done < <(env -0) # pipe in the environment variables

# print the result
echo "$output"

# run yamcs
mvn yamcs:run