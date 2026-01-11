#!/bin/bash
git checkout master && \
git merge --ff-only develop && \
git push origin master && \
echo "Promoted to master - release workflow triggered"
