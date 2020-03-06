FROM ubuntu:18.04

ARG   DEBIAN_FRONTEND=noninteractive
ARG   BUILD_DIR=/usr/local/assembly-stats

# Install the dependancies
RUN   apt-get update && \
      apt-get install --yes apt-utils && \
      apt-get --yes upgrade && \
      apt-get install --yes build-essential cmake

RUN   apt-get install -y locales && \
      sed -i -e 's/# \(en_GB\.UTF-8 .*\)/\1/' /etc/locale.gen && \
      touch /usr/share/locale/locale.alias && \
      locale-gen
ENV   LANG     en_GB.UTF-8
ENV   LANGUAGE en_GB:en
ENV   LC_ALL   en_GB.UTF-8

COPY  . ${BUILD_DIR}
RUN   cd ${BUILD_DIR} && \
      mkdir build && \
      cd build && \
      cmake .. && \
      make && \ 
      make test  && \
      make install
RUN   cd ${BUILD_DIR}/build && \
      make clean && \
      cd .. && \
      rm -r build && \
      apt-get remove --yes build-essential cmake

CMD   echo "Usage:  docker run -v \`pwd\`:/var/data -it <IMAGE_NAME> bash"; \
      echo ""; \
      echo "This will place you in a shell with your current working directory accessible as /var/data."; \
      echo "" ;\
      echo "For help:"; \
      echo "   assembly-stats"
