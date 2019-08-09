sort(xpos.begin(), xpos.end());
xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
tot = 1;
lpos[1] = rpos[1] = xpos[1];
sz[1] = 1;
for (int i = 2; i < xpos.size(); ++i) {
    if (xpos[i] - xpos[i - 1] != 1) {
        lpos[++tot] = xpos[i - 1] + 1;
        rpos[tot] = xpos[i] - 1;
        sz[tot] = rpos[tot] - lpos[tot] + 1;
    }
    ++tot;
    lpos[tot] = rpos[tot] = xpos[i];
    sz[tot] = 1;
}