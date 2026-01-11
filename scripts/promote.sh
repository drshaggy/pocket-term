#!/bin/bash
git checkout master && \
git merge --ff-only develop && \
git push origin master && \
git checkout develop && \
echo "Promoted to master - release workflow triggered"
