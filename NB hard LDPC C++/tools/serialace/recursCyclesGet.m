function cyclesCell = recursCyclesGet( vNodeTarget, vNodeParent, cNodeParent, H, maxDepth, visNodeSet )
    cyclesCell = {};
    
    tempCell = recursCyclesGet_( vNodeTarget, vNodeParent, cNodeParent, H, maxDepth, visNodeSet );
    for k = 1:length(tempCell)
        tempCycle = tempCell{k};
        tempCycle = [vNodeTarget, tempCycle];
        cyclesCell = [cyclesCell {tempCycle}];
    end 
end


function cyclesCell = recursCyclesGet_( vNodeTarget, vNodeParent, cNodeParent, H, maxDepth, visNodeSet )

    cyclesCell = {};

    if maxDepth == 0
        return;
    end

    n = size(H, 2);

    cNeibours = n + find(H(:, vNodeParent));
    cNeibours = cNeibours(cNeibours ~= cNodeParent);
    %cNeibours = cNeibours(~ismember(cNeibours, visNodeSet));
    cNeibours = setdiff(cNeibours, visNodeSet);
    if isempty(cNeibours)
        return;
    end
    for i = 1:length(cNeibours)
        vNeibours = find(H(cNeibours(i) - n, :))';
        vNeibours = vNeibours(vNeibours ~= vNodeParent);
        if any(vNeibours == vNodeTarget)
            cyclesCell = {cyclesCell{:}, cNeibours(i)};
            vNeibours = vNeibours(vNeibours ~= vNodeTarget);
        end
        vNeibours = vNeibours(~ismember(vNeibours, visNodeSet));
        if isempty(vNeibours)
            continue; % krsch: Was break earlier
        end
        for j = 1:length(vNeibours)
            currCyclesCell = recursCyclesGet_(vNodeTarget, ...
                                              vNeibours(j), ...
                                              cNeibours(i), ...
                                              H, ...
                                              maxDepth-2, ... 
                                              unique([visNodeSet cNeibours(i) vNeibours(j)]) );
            tempCyclesCell = {};
            for k = 1:length(currCyclesCell)
                tempCycle = currCyclesCell{k};
                tempCycle = [cNeibours(i), vNeibours(j), tempCycle];
                tempCyclesCell = {tempCyclesCell{:}, tempCycle};
            end
            cyclesCell = {cyclesCell{:}, tempCyclesCell{:}};
        end
    end
end

